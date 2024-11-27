#define APOSPOS 26
#define MAXSTR 50

/*
Adds letters in string 'w' to dict pointer 'c'
*/
dict* add_letters(dict* c, const char* w);

/*
Adds a letter to the tree.
Allocates space. Returns pointer to added letter. Returns
NULL if p is null.
*/
dict* add_letter(dict *p, int idx);

/*
Convert a character to index 0-26.
Character 27 is the apostrophe. Letters can be upper or
lower case. Returns -1 if the character is not valid.
*/
int char_to_ind(char a);

/*
Returns the length of a word.
Takes a pointer to the terminal node of a word.
*/
int dict_length(dict* p);

/*
Finds a related route if it exists.
Takes the terminal nodes of two words. If one is a
substring of the other, or they branch off from the same
substring, then the distance between the two nodes is
returned. Else -1 is returned.
*/
int related_route(dict* lp, dict *sp);

/*
Finds distance from terminal to 'node' in 'sd'.
Returns -1 if not found.
*/
int node_shared(dict* node, dict* sd);

/*
Finds the most frequent word ending.
Returns a dict pointer to first terminal node with 'max'
frequency. Returns NULL if not found.
*/
dict* most_freq_end(dict* cur, int max);

/*
Converts a node to it's word as a string.
Uses pointers to terminal node 'cur' and start node.
Returns NULL either pointer is NULL.
*/
char* build_string(dict* cur, dict* start, char* str);

/*
Converts a dict pointer to it's char value.
Returns -1 if 'd' is NULL.
*/
char dict_to_char(dict * d);

/*
Converts an index to a char.
Letters become lower case. Returns -1 if 'a' is not valid.
*/
char ind_to_char(int a);


