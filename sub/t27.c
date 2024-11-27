#include "t27.h"

#define APOSPOS 26
#define MAXSTR 50

/*
Adds letters in string 'w' to dict pointer 'c'
*/
dict* add_letters(dict* c, const char* w);

/*
Adds a letter to the tree.
Allocates space. Returns pointer to added letter. Returns
NULL if p is null.
*/
dict* add_letter(dict *p, int idx);

/*
Convert a character to index 0-26.
Character 27 is the apostrophe. Letters can be upper or
lower case. Returns -1 if the character is not valid.
*/
int char_to_ind(char a);

/*
Returns the length of a word.
Takes a pointer to the terminal node of a word.
*/
int dict_length(dict* p);

/*
Finds a related route if it exists.
Takes the terminal nodes of two words. If one is a
substring of the other, or they branch off from the same
substring, then the distance between the two nodes is
returned. Else -1 is returned.
*/
int related_route(dict* lp, dict *sp);

/*
Finds distance from terminal to 'node' in 'sd'.
Returns -1 if not found.
*/
int node_shared(dict* node, dict* sd);

/*
Finds the most frequent word ending.
Returns a dict pointer to first terminal node with 'max'
frequency. Returns NULL if not found.
*/
dict* most_freq_end(dict* cur, int max);

/*
Converts a node to it's word as a string.
Uses pointers to terminal node 'cur' and start node.
Returns NULL either pointer is NULL.
*/
char* build_string(dict* cur, dict* start, char* str);

/*
Converts a dict pointer to it's char value.
Returns -1 if 'd' is NULL.
*/
char dict_to_char(dict * d);

/*
Converts an index to a char.
Letters become lower case. Returns -1 if 'a' is not valid.
*/
char ind_to_char(int a);


dict* dict_init(void)
{
   dict *head = calloc(1, sizeof(dict));
   if (head == NULL) {
      printf("error: pointer is null\n");
      exit(EXIT_FAILURE);
   }
   return head;
}

bool dict_addword(dict* p, const char* wd)
{
   if (p== NULL || wd == NULL) {
      return false;
   }
   dict *cur = add_letters(p, wd);
   // first occurence
   if (!cur->terminal) {
      cur->terminal = true;
   }
   else {
      return false;
   }
   return true;
}

int dict_nodecount(const dict* p)
{
   int nodes = 0;
   // base
   if (p == NULL) {
      return nodes++;
   }
   for (int i = 0; i < ALPHA; i++) {
      if (p->dwn[i] != NULL) {
         // recursive. sums nodes
         nodes += dict_nodecount(p->dwn[i]);
      }
   }
   return nodes+1;
}

int dict_wordcount(const dict* p)
{
   int words = 0;
   // base case
   if (p == NULL) {
      return words++;
   }
   for (int i = 0; i < ALPHA; i++) {
      if (p->dwn[i] != NULL) {
         if (p->dwn[i]->terminal) {
            words += p->dwn[i]->freq;
         }
         // recursive. sums frequency count
         words += dict_wordcount(p->dwn[i]);
      }
   }
   return words;
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
      // if valid character
      if ((idx = char_to_ind(str[i])) != -1) {
         // is letter there?
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

void dict_free(dict** d)
{
   if (*d == NULL) {
      return;
   }
   for (int i = 0; i < ALPHA; i++) {
      if ((*d)->dwn[i] != NULL) {
         dict_free(&((*d)->dwn[i]));
      }
   }
   free(*d);
   *d = NULL;
}

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

unsigned dict_cmp(dict* p1, dict* p2)
{
   int l1 = dict_length(p1);
   int l2 = dict_length(p2);
   int res;
   // shorter route
   if (l1 > l2) {
      if ((res = related_route(p1, p2))) {
         return res;
      }
   }
   // catches l2>l1 and l2==l1
   else {
      if ((res = related_route(p2, p1))) {
         return res;
      }
   }
   // longer route
   return l1 + l2;
}

void dict_autocomplete(const dict* p, const char* wd, char* ret)
{
   dict * cur = (dict *)p;
   if (cur == NULL) {
      return;
   }
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
   // make string
   if (build_string(end, cur, buffer) != NULL) {
      strcpy(ret, buffer);
   }
   return;
}

dict* add_letters(dict* c, const char* w)
{
   int ind;
   int length = strlen(w);
   for (int i = 0; i < length; i++) {
      // if char is valid
      if ((ind = char_to_ind(w[i])) != -1) {
         // if empty add letter
         if (c->dwn[ind] == NULL) {
            c = add_letter(c, ind);
         }
         // otherwise chase pointer
         else {
            c = c->dwn[ind];
         }
      }
   }
   c->freq++;
   return c;
}

dict* add_letter(dict *p, int idx)
{
   dict *letter = calloc(1, sizeof(dict));
   if (letter == NULL) {
      return NULL;
   }
   p->dwn[idx] = letter;
   letter->up = p;
   return letter;
}

int char_to_ind(char a)
{
   if (a == '\'') {
      return APOSPOS;
   }
   else if (isupper(a)) {
      return a - 'A';
   }
   else if (islower(a)) {
      return a - 'a';
   }
   else {
      return -1;
   }
}

int dict_length(dict* p)
{
   int l = 0;
   while (p->up != NULL) {
      l++;
      p = p->up;
   }
   return l;
}

int related_route(dict* ld, dict *sd)
{
   int a = 0;
   int b = 0;
   dict* cur = ld;
   while (cur->up != NULL) {
      a++;
      cur = cur->up;
      if (cur == sd) {
         return a;
      }
      // loop around
      b = node_shared(cur, sd);
      if (b != -1) {
         return a + b;
      }
   }
   return -1;
}

int node_shared(dict* node, dict* sd)
{
   int a = 0;
   while (sd->up != NULL) {
      sd = sd->up;
      a++;
      if (node == sd) {
         return a;
      }
   }
   return -1;
}

dict* most_freq_end(dict* cur, int max)
{
   dict* temp;
   dict* result = NULL;
   // base
   if (cur->freq == max) {
      result = cur;
   }
   for (int i = 0; i < ALPHA; i++) {
      if (cur->dwn[i] != NULL) {
         // recursive. returns first match
         temp = most_freq_end(cur->dwn[i], max);
         if (temp != NULL) {
               return temp;
         }
      }
   }
   return result;
}

char* build_string(dict* cur, dict* start, char* str)
{
    static int strpos = 0;
    if (cur == NULL || start == NULL) {
        return NULL;
    }
    // base case
    if (cur == start) {
            strpos = 0;
        return NULL;
    }
    char c = dict_to_char(cur);
    // recursive call
    if (cur->up) {
        build_string(cur->up, start, str);
    }
    // append
    str[strpos++] = c;
    str[strpos] = '\0';
    return str;
}

char dict_to_char(dict * d)
{
   if (d == NULL) {
      return -1;
   }
   int pos = 0;
   // find index of node
   dict * prev = d->up;
   for (int i = 0; i < ALPHA; i++) {
      if (prev && prev->dwn[i] == d) {
         pos = i;
      }
   }
   char c = ind_to_char(pos);
   return c;
}

char ind_to_char(int ch)
{
   if ((ch >= 0) && (ch < APOSPOS)) {
      return ch + 'a';
   }
   else if (ch == APOSPOS) {
      return '\'';
   }
   else {
      return -1;
   }
}

void test(void)
{
   assert(char_to_ind('a') == 0);
   assert(char_to_ind('\'') == 26);
   assert(char_to_ind('x') == 23);

   assert(ind_to_char(0) == 'a');
   assert(ind_to_char(26) == '\'');
   assert(ind_to_char(23) == 'x');

   dict* d = dict_init();
   dict_addword(d, "car");
   dict_addword(d, "parted");
   assert(dict_to_char(d->dwn[15]) == 'p');
   assert(dict_to_char(d->dwn[2]) == 'c');

   dict_free(&d);
   free(d);
}
