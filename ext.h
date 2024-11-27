#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct node {
   char *word;
   int freq;
   struct node *r;
   struct node *l;
};

typedef struct {
   struct node *root;
   int node_count;
   int word_count;
} dict;

// Creates new dictionary
dict* dict_init(void);

/* Top of Dictionary = p,
   add word str. Return false
   if p or str is NULL, or if word
   is already in the dictionary.
   True otherwise.
*/
bool dict_addword(dict* p, const char* wd);

/* The total number of nodes
   in the tree. */
int dict_nodecount(const dict* p);

/* Total number of times that any words
   have been added into the tree =
   sum of freq count of all terminals.*/
int dict_wordcount(const dict* p);

/* Returns the dict* where str is
   marked as 'terminal', or else NULL.
*/
dict* dict_spell(const dict* p, const char* str);

/* Frees all memory used by dictionary p.
   Sets the original pointer back to NULL */
void dict_free(dict** p);

/* Returns number of times most common
   word in dictionary has been added
   (when you insert a word and it already
   exists, increment the count)
*/
int dict_mostcommon(const dict* p);

void test(void);

void print_dict_state(const dict* p);


void store_in_order(struct node* root, struct node** nodes, int* index);

struct node* build_balanced_bst(struct node** nodes, int start, int end);
