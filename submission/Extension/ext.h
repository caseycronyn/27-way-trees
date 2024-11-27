#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BALANCELIM 1000

struct node {
   char* word;
   int freq;
   struct node* r;
   struct node* l;
};

typedef struct {
   struct node* root;
   int node_count;
   int word_count;
} dict;

// Adds word to bin tree
bool dict_addword(dict* p, const char* wd);

// Counts nodes in dict
int dict_nodecount(const dict* p);

// Calls free_nodes, freeing space
void dict_free(dict** p);

// Finds most common element, returning its frequency
int dict_mostcommon(const dict* p);

// Counts words in dict, returning this as an int
int dict_wordcount(const dict* p);

// Prints current state of dict
void print_dict_state(const dict* p);

// Recursively stores the elements either side of the root
void store_in_order(struct node* root, struct node** nodes,
                    int* index);

// Balances the tree recursively. Called by dict_balance
struct node* build_balanced_bst(struct node** nodes,
                                int start, int end);

// finds node based on target str
struct node* search(struct node* root, const char* str);

// Same as t27
dict* dict_init(void);

// Same as t27
dict* dict_spell(const dict* p, const char* str);

// Same as t27
void test(void);