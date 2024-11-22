#include "t27.h"
#include "mydefs.h"

// add to t27.c
int main(void)
{
   assert(char_to_ind('A') == 0);
   assert(char_to_ind('\'') == 26);
   assert(char_to_ind('x') == 23);

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
   dict_addword(d, "part");
   // dict_addword(d, "parted");
   // dict_addword(d, "parter");
   dict_free(&d);


   // free(child2);
   // free(child);
   free(d);
   printf("~\n");
   return 0;
}