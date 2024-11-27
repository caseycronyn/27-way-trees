#include "t27.h"
#include "mydefs.h"

// add to t27.c
int main(void)
{
   assert(char_to_ind('a') == 0);
   assert(char_to_ind('\'') == 26);
   assert(char_to_ind('x') == 23);

   assert(ind_to_char(0) == 'a');
   assert(ind_to_char(26) == '\'');
   assert(ind_to_char(23) == 'x');

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
   dict_addword(d, "car");
   // dict_addword(d, "par");
   // printf("%d\n", dict_wordcount(d));

   // p=15, a=0, r=17
   // assert(dict_nodecount(d) == 4);
   // printf("%d\n", dict_nodecount(d));
   dict_addword(d, "part");
   // + 19
   // printf("%d\n", dict_nodecount(d));
   // assert(dict_nodecount(d) == 5);
   dict_addword(d, "parted");
   assert(dict_nodecount(d) == 10);
   assert(dict_to_char(d->dwn[15]) == 'p');
   assert(dict_to_char(d->dwn[2]) == 'c');

   dict_addword(d, "partay");
   dict_addword(d, "partay");
   // t = 19 

   char str[MAXSTR];

   dict_autocomplete(d, "part", str);
   // printf("%s\n", str);
   // printf("%d\n", dict_wordcount(d));
   // assert(dict_wordcount(d) == 5);
   // printf("%d\n", dict_nodecount(d));
   // assert(dict_nodecount(d) == 8);
   // printf("%d\n", dict_mostcommon(d));
   // dict_mostcommon(d);
   dict_free(&d);


   // free(child2);
   // free(child);
   free(d);
   printf("~\n");
   return 0;
}
