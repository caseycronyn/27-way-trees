#include "t27.h"
#include "mydefs.h"

// add to t27.c
int main(void)
{
   assert(char_to_ind('A') == 0);
   assert(char_to_ind('\'') == 26);
   assert(char_to_ind('x') == 23);

   assert(dict_nodecount(NULL)==0);

   dict* d = dict_init();
   // print_addresses(d);
   // dict* child = add_letter(d, 'A');
   // dict_free(&d);
   // print_addresses(d);
   // dict* child2 = add_letter(child, '\'');
   // child = add_letter(child, 'z');
   // int *d = d->dwn[0];

   // dict_addword(d, "A\'x");
   dict_addword(d, "par");
   // dict_addword(d, "par");
   // printf("%d\n", dict_wordcount(d));

   // 15, 0, 17
   // assert(dict_nodecount(d) == 4);
   // printf("%d\n", dict_nodecount(d));
   dict_addword(d, "part");
   // + 19
   // printf("%d\n", dict_nodecount(d));
   // assert(dict_nodecount(d) == 5);
   dict_addword(d, "parted");
   assert(dict_nodecount(d) == 7);
   dict_addword(d, "parter");
   // printf("%d\n", dict_wordcount(d));
   // assert(dict_wordcount(d) == 5);
   // printf("%d\n", dict_nodecount(d));
   assert(dict_nodecount(d) == 8);
   printf("%d\n", dict_mostcommon(d));
   // dict_mostcommon(d);
   dict_free(&d);


   // free(child2);
   // free(child);
   free(d);
   printf("~\n");
   return 0;
}
