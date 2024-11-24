#define APOSPOS 26

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
char* build_string(dict* end, dict* prev, dict* start, char* str);

// on the tin
char* reverse_string(char* str);

// indices to char.
char ind_to_char(int a);
