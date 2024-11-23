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
