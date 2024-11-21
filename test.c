#include "t27.h"
#include "mydefs.h"

// add to t27.c
int main(void)
{
   assert(char_to_ind('A') == 0);
   assert(char_to_ind('\'') == 26);
   assert(char_to_ind('x') == 23);

   dict* head = dict_init();
   // print_addresses(head);
   dict* child = add_letter(head, 'A');
   // dict_free(&head);
   // print_addresses(head);
   dict* child2 = add_letter(child, '\'');
   // child = add_letter(child, 'z');
   // int *d = head->dwn[0];

   free(child2);
   free(child);
   free(head);
   printf("#\n");
   return 0;
}