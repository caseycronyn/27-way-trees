#include "ext.h"

dict* dict_init(void)
{
   dict* d = malloc(sizeof(dict));
   if (d == NULL) {
      fprintf(stderr, "error: dict pointer d is NULL");
      exit(EXIT_FAILURE);
   }
   d->root = NULL;
   d->node_count = 0;
   d->word_count = 0;
   return d;
}

void dict_balance(dict* p)
{
   if (p == NULL || p->root == NULL) {
      return;
   }
   int node_count = p->node_count;
   // allocates nodes
   struct node** nodes =
       malloc(node_count * sizeof(struct node*));
   if (nodes == NULL) {
      printf("error: nodes pointer is null");
      return;
   }
   int index = 0;
   // order nodes, then balance the bst
   store_in_order(p->root, nodes, &index);
   p->root = build_balanced_bst(nodes, 0, node_count - 1);
   free(nodes);
}

void store_in_order(struct node* root, struct node** nodes,
                    int* index)
{
   // base
   if (root == NULL) {
      return;
   }
   // recursive
   store_in_order(root->l, nodes, index);
   nodes[(*index)++] = root;
   store_in_order(root->r, nodes, index);
}

struct node* build_balanced_bst(struct node** nodes,
                                int start, int end)
{
   // base
   if (start > end) {
      return NULL;
   }
   int mid = (start + end) / 2;
   struct node* root = nodes[mid];
   // recursive
   root->l = build_balanced_bst(nodes, start, mid - 1);
   root->r = build_balanced_bst(nodes, mid + 1, end);
   return root;
}

struct node* new_node(const char* str)
{
   struct node* temp = malloc(sizeof(struct node));
   if (temp == NULL) {
      fprintf(stderr, "error: temp is NULL");
      exit(EXIT_FAILURE);
   }
   temp->word = malloc(strlen(str) + 1);
   if (temp->word == NULL) {
      fprintf(stderr, "error: temp->word is NULL");
      free(temp);
      exit(EXIT_FAILURE);
   }
   // update values
   strcpy(temp->word, str);
   temp->freq = 1;
   temp->l = NULL;
   temp->r = NULL;

   return temp;
}

void to_lowercase(char* str)
{
   for (; *str; ++str) {
      *str = tolower(*str);
   }
}

struct node* insert(struct node* root, const char* str,
                    int* node_count, bool* is_new_word)
{
   // base case
   if (root == NULL) {
      (*node_count)++;
      *is_new_word = true;
      return new_node(str);
   }
   // branch left/ right
   int cmp = strcmp(str, root->word);
   if (cmp == 0) {
      root->freq++;
      *is_new_word = false;
      // recursive calls on both sides
   } else if (cmp > 0) {
      root->r =
          insert(root->r, str, node_count, is_new_word);
   } else {
      root->l =
          insert(root->l, str, node_count, is_new_word);
   }
   return root;
}

bool dict_addword(dict* p, const char* str)
{
   if (p == NULL || str == NULL) return false;

   char* lower_str = malloc(strlen(str) + 1);
   if (lower_str == NULL) {
      printf("error: lower_str is NULL");
      return false;
   }
   // format str
   strcpy(lower_str, str);
   to_lowercase(lower_str);
   bool is_new_word = false;
   // insert
   p->root = insert(p->root, lower_str, &p->node_count,
                    &is_new_word);
   p->word_count++;
   free(lower_str);
   // keeps track of insertions
   static int insertion_count = 0;
   insertion_count++;
   // limiting condition
   if (insertion_count >= BALANCELIM) {
      dict_balance(p);
      insertion_count = 0;
   }
   return is_new_word;
}

struct node* search(struct node* root, const char* str)
{
   if (root == NULL) {
      return NULL;
   }
   int cmp = strcmp(str, root->word);
   // base
   if (cmp == 0) {
      return root;
      // recursive calls on r/ l
   } else if (cmp > 0) {
      return search(root->r, str);
   } else {
      return search(root->l, str);
   }
}

dict* dict_spell(const dict* p, const char* str)
{
   if (p == NULL || str == NULL) {
      return NULL;
   }
   char* lower_str = malloc(strlen(str) + 1);
   if (lower_str == NULL) {
      printf("error: lower_str is NULL");
      return NULL;
   }
   // format string
   strcpy(lower_str, str);
   to_lowercase(lower_str);
   struct node* result = search(p->root, lower_str);
   free(lower_str);
   // if word found
   if (result) {
      return (dict*)p;
   } else {
      return NULL;
   }
}

int dict_nodecount(const dict* p)
{
   if (p) {
      return p->node_count;
   }
   return 0;
}

int dict_wordcount(const dict* p)
{
   if (p) {
      return p->word_count;
   }
   return 0;
}

void find_most_common(struct node* root,
                      struct node** most_common)
{
   // base case
   if (root == NULL) {
      return;
   }
   if (*most_common == NULL ||
       root->freq > (*most_common)->freq) {
      *most_common = root;
   }
   // recursive
   find_most_common(root->l, most_common);
   find_most_common(root->r, most_common);
}

int dict_mostcommon(const dict* p)
{
   if (p == NULL || p->root == NULL) {
      return 0;
   }
   struct node* most_common = NULL;
   find_most_common(p->root, &most_common);
   // if successful
   if (most_common) {
      return most_common->freq;
   }
   return 0;
}

void free_nodes(struct node* root)
{
   // base
   if (root == NULL) {
      return;
   }
   // recursive calls
   free_nodes(root->l);
   free_nodes(root->r);
   free(root->word);
   free(root);
}

void dict_free(dict** p)
{
   // check if NULL
   if (p && *p) {
      free_nodes((*p)->root);
      free(*p);
      *p = NULL;
   }
}

void print_tree_state(struct node* root, int depth)
{
   if (root == NULL) return;
   print_tree_state(root->l, depth + 1);
   printf("word: '%s', depth: %d, freq: %d\n", root->word,
          depth, root->freq);
   print_tree_state(root->r, depth + 1);
}

void print_dict_state(const dict* p)
{
   if (p == NULL || p->root == NULL) {
      fprintf(stderr, "Dictionary is empty.\n");
      exit(EXIT_FAILURE);
   }
   // success
   printf("Printing tree state:\n");
   print_tree_state(p->root, 0);
}

void test(void)
{
   dict* my_dict = dict_init();
   dict_addword(my_dict, "apple");
   dict_addword(my_dict, "banana");
   dict_addword(my_dict, "cherry");
   dict_addword(my_dict, "date");
   dict_addword(my_dict, "elderberry");
   dict_free(&my_dict);
}

