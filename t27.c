#include "t27.h"
#include "mydefs.h"

// 'Internal' function prototypes 
// ...

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
   dict *tmp = NULL;
   dict *cur = p;
   int length = strlen(wd);
   for (int i = 0; i < length; i++) {
      // if (cur)
      tmp = add_letter(cur, wd[i]);
      cur = tmp;
   }
   cur->terminal = true;
   return true;
}

dict *add_letter(dict *p, char C)
{
   dict *letter = calloc(1, sizeof(dict));
   if (letter == NULL) {
      printf("error: letter pointer is null");
      exit(EXIT_FAILURE);
   }
   int ind = char_to_ind(C);
   p->dwn[ind] = letter;
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

void print_addresses(dict* d)
{
   for (int i = 0; i < ALPHA; i++) {
      // printf("%2d: %10x\n", i, d->dwn[i]);
      if (d->dwn[i] != 0) {
         printf("%2d\n", i);
      }
   }
}

void dict_free(dict** d)
{
   if ((*d)->terminal) {
      free(*d);
      *d = NULL;
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

// int dict_wordcount(const dict* p)
// {
// }

// int dict_nodecount(const dict* p)
// {
// }

// dict* dict_spell(const dict* p, const char* str)
// {
// }

// int dict_mostcommon(const dict* p)
// {
// }

// // CHALLENGE1
// unsigned dict_cmp(dict* p1, dict* p2)
// {
// }

// // CHALLENGE2
// void dict_autocomplete(const dict* p, const char* wd, char* ret)
// {
// }