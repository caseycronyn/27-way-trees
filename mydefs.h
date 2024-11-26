#define APOSPOS 26
#define MAXSTR 50

/*
adds a letter to the tree, allocating space.
returns pointer to added letter
called by add_word
*/
dict *add_letter(dict *p, int idx);

/*
convert a character to index 0-26
character 27 is apostrophe " ' "
case insensitive
return -1 if invalid character
*/
int char_to_ind(char a);

// print the emory addresses of the dictionary->down
// void print_addresses(dict * d);

// finds word. returns false if not found
bool word_is_found(const dict* p, char c);

// returns pointer to node of most frequent word ending based on starting node and max frequency. return null if it fails
dict* most_freq_end(dict* cur, int max);

// builds string in reverse
char* build_string(dict* cur, dict* start, char* str);

// on the tin
// char* reverse_string(char* str);

// indices to char.
char ind_to_char(int a);

// given a dict *, return it's character. -1 if error
char dict_to_char(dict * d);

int dict_length(dict* p);

// calculates if the route is on the same branch or branches off from the same one. -1 for false
int on_route(dict* lp, dict *sp);

// return node position from terminal in sd if node exists within, else -1
int node_shared(dict* node, dict* sd);

// on da tino
dict* add_letters(dict* c, const char* w);
