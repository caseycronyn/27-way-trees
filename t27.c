#include "t27.h"
#include "mydefs.h"

//TODO replace code blocks with dict_to_char
dict* dict_init(void)
{
   dict *head = calloc(1, sizeof(dict));
   if (head == NULL) {
      printf("error: pointer is null\n");
      exit(EXIT_FAILURE);
   }
   // head->dwn[0] = NULL;
   // for (int i = 0; i < ALPHA-1; i++) {
   //    head->dwn[i] = NULL;
   // }
   return head;
}

bool dict_addword(dict* p, const char* wd)
{
   if (p== NULL || wd == NULL) {
      return false;
   }
   int ind;
   dict *cur = p;
   int length = strlen(wd);
   for (int i = 0; i < length; i++) {
      // if char is valid
      if ((ind = char_to_ind(wd[i])) != -1) {
         // if empty add letter
         if (cur->dwn[ind] == NULL) {
            cur = add_letter(cur, ind);
         }
         // ptr chase to next position
         else {
            cur = cur->dwn[ind];
         }
      }
   }
   cur->freq++;
   // first occurence
   if (!cur->terminal) {
      cur->terminal = true;
   }
   else {
      return false;
   }
   return true;
}

dict *add_letter(dict *p, int idx)
{
   dict *letter = calloc(1, sizeof(dict));
   if (letter == NULL) {
      printf("error: letter pointer is null");
      exit(EXIT_FAILURE);
   }
   p->dwn[idx] = letter;
   letter->up = p;
   return letter;
}

int char_to_ind(char a)
{
   int val;
   
   if (a == '\'') {
      val = APOSPOS;
   }
   else if (isupper(a)) {
      val = a - 'A';
   }
   else if (islower(a)) {
      val = a - 'a';
   }
   else {
      val = -1;
   }
   return val;
}

// void print_addresses(dict* d)
// {
//    for (int i = 0; i < ALPHA; i++) {
//       // printf("%2d: %10x\n", i, d->dwn[i]);
//       if (d->dwn[i] != 0) {
//          printf("%2d\n", i);
//       }
//    }
// }

void dict_free(dict** d)
{
   // base case
   if ((*d)->terminal) {
      free(*d);
      *d = NULL;
      return;
   }
   // loop through all letters for all nodes
   for (int i = 0; i < ALPHA; i++) {
      if ((*d)->dwn[i] != NULL) {
         dict_free(&((*d)->dwn[i]));
      }
   }
   free(*d);
   *d = NULL;
}

int dict_wordcount(const dict* p)
{
   int words = 0;
   if (p == NULL) {
      return words++;
   }
   for (int i = 0; i < ALPHA; i++) {
      if (p->dwn[i] != NULL) {
         if (p->dwn[i]->terminal) {
            words += p->dwn[i]->freq;
         }
         words += dict_wordcount(p->dwn[i]);
      }
   }
   return words;
}

int dict_nodecount(const dict* p)
{
   int nodes = 0;
   if (p == NULL) {
      return nodes++;
   }
   for (int i = 0; i < ALPHA; i++) {
      if (p->dwn[i] != NULL) {
         nodes += dict_nodecount(p->dwn[i]);
      }
   }
   return nodes+1;
}

dict* dict_spell(const dict* p, const char* str)
{
   if (p == NULL || str == NULL) {
      return NULL;
   }
   int idx;
   dict *cur = (dict *)p;
   int length = strlen(str);
   for (int i = 0; i < length; i++) {
      if ((idx = char_to_ind(str[i])) != -1) {
         // is letter there?
         // if not return false
         if (cur == NULL || cur->dwn[idx] == NULL) {
            return NULL;
         }
         // if so, walk pointer
         cur = cur->dwn[idx];
      }
   }
   if (!cur->terminal) {
      cur = NULL;
   }
   return cur;
}

// bool letter_found(const dict* p, char c)
// {

// }

int dict_mostcommon(const dict* p)
{
   int mo_ov, cur, call, mo_cur_call;
   mo_ov = 0;
   // base case
   if (p == NULL) {
      return 0;
   }
   for (int i = 0; i < ALPHA; i++) {
      if (p->dwn[i] != NULL) {
         cur = p->dwn[i]->freq;
         // recursive call
         call = dict_mostcommon(p->dwn[i]);
         mo_cur_call = (cur > call) ? cur : call;
         // update mo_ov if latest call is more
         mo_ov = (mo_cur_call > mo_ov) ? mo_cur_call : mo_ov;
      }
   }
   return mo_ov;
}

// CHALLENGE1. pointers are terminal nodes
unsigned dict_cmp(dict* p1, dict* p2)
{
   int l1, l2;
   l1 = l2 = 0;
   while (p1->up != NULL) {
      l1++;
      p1 = p1->up;
   }
   while (p2->up != NULL) {
      l2++;
      p2 = p2->up;
   }
   return l1 + l2;
}

// CHALLENGE2
void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
   dict * cur = (dict *)p;
   int idx;
   int len = strlen(wd);
   // move cur to end of word in tree
   for (int i = 0; i < len; i++) {
      if ((idx = char_to_ind(wd[i])) != -1) {
         cur = cur->dwn[idx];
      }
   }
   int max_fre = dict_mostcommon(cur);
   // search for first occurence of most frequent word
   dict* end = most_freq_end(cur, max_fre);
   char buffer[MAXSTR];
   build_string(end, cur, buffer);
   strcpy(ret, buffer);
   // printf("%s\n", ret);
   return;
}

dict* most_freq_end(dict* cur, int max)
{
   // go to ends of branches. record highest scoring frequency with pointer to location.
   dict* tmp = cur;
   for (int i = 0; i < ALPHA; i++) {
      if (tmp->dwn[i] != NULL) {
         tmp = most_freq_end(tmp->dwn[i], max);
      }
   }
   if (tmp->freq == max) {
      return tmp;
   }
   return NULL;
}
// dict* most_freq_end(dict* cur, int max)
// {
//    // go to ends of branches. record highest scoring frequency with pointer to location.
//    dict* tmp = cur;
//    if (tmp->freq == max) {
//       return tmp;
//    }
//    for (int i = 0; i < ALPHA; i++) {
//       if (tmp->dwn[i] != NULL) {
//          tmp = most_freq_end(tmp->dwn[i], max);
//       }
//    }
//    return tmp;
// }

char* build_string(dict* cur, dict* start, char* str)
{
   // base case
   if (cur == start) {
      return NULL;
   }
   static int strpos = 0;
   char c = dict_to_char(cur);
   // recursive call
   build_string(cur->up, start, str);
   str[strpos++] = c;
   str[strpos] = '\0';
   return str;
}

// char* build_string(dict* end, dict* prev, dict* start, char* str)
// {
//    // base case
//    if (prev == start) {
//       return NULL;
//    }
//    int pos = -1;
//    static int strpos = 0;
//    char c;
//       // find character index in node below
//       for (int i = 0; i < ALPHA; i++) {
//          if (end->dwn[i] == prev) {
//             pos = i;
//          }
//       }
//       // recursive call
//       if ((c = ind_to_char(pos)) != -1) {
//          build_string(end->up, end, start, str);
//          str[strpos++] = c;
//          str[strpos] = '\0';
//       }
//    return str;
// }

// given a dict *, return it's character
char dict_to_char(dict * d)
{
   int pos;
   char c;
   dict * prev = d->up;
   // find character index in node below
   for (int i = 0; i < ALPHA; i++) {
      if (prev->dwn[i] == d) {
         pos = i;
      }
   }
   c = ind_to_char(pos);
   return c;
}

char ind_to_char(int ch)
{
   if ((ch >= 0) && (ch < APOSPOS)) {
         ch += 'a';
   }
   else if (ch == APOSPOS) {
         ch = '\'';
   }
   else {
      ch = -1;
   }
   return (char)ch;
}

void test(void)
{
   ;
}
