#include "bst.h"

// Function to create a new node
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

// Initialize the dictionary
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

// Helper function to make strings case-insensitive
void to_lowercase(char *str) {
    for (; *str; ++str) {
        *str = tolower(*str);
    }
}

// Recursive function to add a word to the BST
struct node* insert(struct node *root, const char *str, int *node_count, bool *is_new_word) {
    if (root == NULL) {
        (*node_count)++;
        *is_new_word = true;
        return new_node(str);
    }
    
    int cmp = strcmp(str, root->word);
    if (cmp == 0) {
        root->frequency++;
        *is_new_word = false;  // The word already exists
    } else if (cmp > 0) {
        root->right_child = insert(root->right_child, str, node_count, is_new_word);
    } else {
        root->left_child = insert(root->left_child, str, node_count, is_new_word);
    }
    return root;
}

// Add a word to the dictionary
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
    p->root = insert(p->root, lower_str, &p->node_count, &is_new_word);
    p->word_count++;
    free(lower_str);
    
    return is_new_word;
}

// Search for a word in the BST
struct node* search(struct node *root, const char *str) {
    if (root == NULL) return NULL;

    int cmp = strcmp(str, root->word);
    if (cmp == 0) return root;
    else if (cmp > 0) return search(root->right_child, str);
    else return search(root->left_child, str);
}

// Check if a word is spelled correctly (exists in the dictionary)
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

// Count nodes in the dictionary
int dict_nodecount(const dict* p) {
    return p ? p->node_count : 0;
}

// Count total words in the dictionary
int dict_wordcount(const dict* p) {
    return p ? p->word_count : 0;
}

// Find the most common word in the dictionary
void find_most_common(struct node *root, struct node **most_common) {
    if (root == NULL) return;
    if (*most_common == NULL || root->frequency > (*most_common)->frequency) {
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

// Free the nodes in the BST
void free_nodes(struct node *root) {
    if (root == NULL) return;
    free_nodes(root->left_child);
    free_nodes(root->right_child);
    free(root->word);
    free(root);
}

// Free the dictionary
void dict_free(dict** p) {
    if (p && *p) {
        free_nodes((*p)->root);
        free(*p);
        *p = NULL;
    }
}


void test(void) {
    // Implement any test logic if needed
}