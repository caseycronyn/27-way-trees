#include "ext.h"

#define BALANCELIM 1000

void store_in_order(struct node* root, struct node** nodes, int* index) {
    // base
    if (root == NULL) {
        return;
    }
    // recursive
    store_in_order(root->left_child, nodes, index);
    nodes[(*index)++] = root;
    store_in_order(root->right_child, nodes, index);
}

struct node* build_balanced_bst(struct node** nodes, int start, int end) {
    // base
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    struct node* root = nodes[mid];
    // recursive
    root->left_child = build_balanced_bst(nodes, start, mid - 1);
    root->right_child = build_balanced_bst(nodes, mid + 1, end);
    return root;
}

void dict_balance(dict* p) {
    if (p == NULL || p->root == NULL) {
        return;
    }
    int node_count = p->node_count;
    struct node** nodes = malloc(node_count * sizeof(struct node*));
    if (nodes == NULL) {
        printf("Failed to allocate memory for node array");
        return;
    }
    int index = 0;
    store_in_order(p->root, nodes, &index);
    p->root = build_balanced_bst(nodes, 0, node_count - 1);
    free(nodes);
}

struct node* new_node(const char *str) {
    struct node *temp = malloc(sizeof(struct node));
    if (!temp) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    temp->word = malloc(strlen(str) + 1);
    if (!temp->word) {
        perror("Failed to allocate memory for word");
        free(temp);
        exit(EXIT_FAILURE);
    }
    strcpy(temp->word, str);
    temp->frequency = 1;
    temp->left_child = NULL;
    temp->right_child = NULL;

    return temp;
}

dict* dict_init(void) {
    dict *d = malloc(sizeof(dict));
    if (!d) {
        perror("Failed to allocate memory for dictionary");
        exit(EXIT_FAILURE);
    }
    d->root = NULL;
    d->node_count = 0;
    d->word_count = 0;
    return d;
}

void to_lowercase(char *str) {
    for (; *str; ++str) {
        *str = tolower(*str);
    }
}

struct node* insert(struct node *root, const char *str, int *node_count, bool *is_new_word) {
    if (root == NULL) {
        (*node_count)++;
        *is_new_word = true;
        return new_node(str);
    }
    int cmp = strcmp(str, root->word);
    if (cmp == 0) {
        root->frequency++;
        *is_new_word = false;  
    } else if (cmp > 0) {
        root->right_child = insert(root->right_child, str, 
                                    node_count, is_new_word);
    } else {
        root->left_child = insert(root->left_child, str, 
                                    node_count, is_new_word);
    }
    return root;
}

bool dict_addword(dict* p, const char* str) {
    if (!p || !str) return false;

    char *lower_str = malloc(strlen(str) + 1);
    if (!lower_str) {
        perror("Failed to allocate memory for lower_str");
        return false;
    }
    strcpy(lower_str, str);
    to_lowercase(lower_str);

    bool is_new_word = false;
    p->root = insert(p->root, lower_str, &p->node_count, 
                                            &is_new_word);
    p->word_count++;

    free(lower_str);

    static int insertion_count = 0;
    insertion_count++;

    if (insertion_count >= BALANCELIM) {
        dict_balance(p);
        insertion_count = 0;  
    }

    return is_new_word;
}

struct node* search(struct node *root, const char *str) {
    if (root == NULL) return NULL;

    int cmp = strcmp(str, root->word);
    if (cmp == 0) return root;
    else if (cmp > 0) return search(root->right_child, str);
    else return search(root->left_child, str);
}

dict* dict_spell(const dict* p, const char* str) {
    if (!p || !str) return NULL;
    char *lower_str = malloc(strlen(str) + 1);
    if (!lower_str) {
        perror("Failed to allocate memory for lower_str");
        return NULL;
    }
    strcpy(lower_str, str);
    to_lowercase(lower_str);
    struct node* result = search(p->root, lower_str);
    free(lower_str);
    return result ? (dict*)p : NULL;
}

int dict_nodecount(const dict* p) {
    int count = p ? p->node_count : 0;
    return count;
}

int dict_wordcount(const dict* p) {
    int count = p ? p->word_count : 0;
    return count;
}

void find_most_common(struct node *root, 
                        struct node **most_common) {
    if (root == NULL) return;
    if (*most_common == NULL || 
        root->frequency > (*most_common)->frequency) {
        *most_common = root;
    }
    find_most_common(root->left_child, most_common);
    find_most_common(root->right_child, most_common);
}

int dict_mostcommon(const dict* p) {
    if (!p || !p->root) return 0;
    struct node *most_common = NULL;
    find_most_common(p->root, &most_common);
    return most_common ? most_common->frequency : 0;
}

void free_nodes(struct node *root) {
    if (root == NULL) return;
    free_nodes(root->left_child);
    free_nodes(root->right_child);
    free(root->word);
    free(root);
}

void dict_free(dict** p) {
    if (p && *p) {
        free_nodes((*p)->root);
        free(*p);
        *p = NULL;
    }
}

void print_tree_state(struct node* root, int depth) { if (root == NULL) return;
    print_tree_state(root->left_child, depth + 1);

    printf("Word: '%s', Frequency: %d, Depth: %d\n", root->word, root->frequency, depth);

    // right
    print_tree_state(root->right_child, depth + 1);
}

void print_dict_state(const dict* p) {
    if (!p || !p->root) {
        printf("Dictionary is empty.\n");
        return;
    }
    printf("Printing tree state:\n");
    print_tree_state(p->root, 0);
}

void test(void) {
    dict* my_dict = dict_init();
    dict_addword(my_dict, "apple");
    dict_addword(my_dict, "banana");
    dict_addword(my_dict, "cherry");
    dict_addword(my_dict, "date");
    dict_addword(my_dict, "elderberry");
    // print_dict_state(my_dict);
    dict_free(&my_dict);
}
