#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ext.h"

#define MAXSTR 100
#define DICTFILES 17
#define LOOPS 1

int main(void)
{
   clock_t start, end;
   double cpu_time_used;
   start = clock();

   char dictnames[DICTFILES][MAXSTR] = {
       "Words/3words.txt",
       "Words/sense-and-sensiblity.txt",
       "Words/s-and-s-words.txt",
       "Words/eowl_sorted.txt",
       "Words/english_65197.txt",
       "Words/eowl_shuffle.txt",
       "Words/4words.txt",
       "Words/p-and-p-words.txt",
       "Words/words_alpha.txt",
       "Words/pride-and-prejudice.txt",
       "Words/sherlock_holmes.txt",
       "Words/cmudict-0.7b.txt",
       "Words/jane_austin.txt",
       "Words/34words.txt",
       "Words/h-of-d.txt",
       "Words/eng_370k_shuffle.txt",
       "Words/wordle.txt"};
   int mostc[DICTFILES] = {0};

   dict* dcts[DICTFILES];

   int l = 0;
   while (l < LOOPS) {
      for (int i = 0; i < DICTFILES; i++) {
         dict* d = dict_init();
         dcts[i] = d;
         assert(d);
         FILE* fp = fopen(dictnames[i], "rt");
         if (!fp) {
            fprintf(stderr, "Cannot open word file %s\n",
                    dictnames[i]);
            exit(EXIT_FAILURE);
         }
         char str[MAXSTR];
         while (fgets(str, MAXSTR, fp) != NULL) {
            char str2[MAXSTR];
            sscanf(str, "%s", str2);
            if (mostc[i] == 1) {
               assert(dict_spell(d, str2) == NULL);
            }
            dict_addword(d, str2);
            assert(dict_spell(d, str2));
         }
         fclose(fp);
         l++;
      }
   }

   // Free up all those dictionaries
   for (int i = 0; i < DICTFILES; i++) {
      dict_free(&dcts[i]);
   }

   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Program took %f seconds to execute. \n",
          cpu_time_used);
   return 0;
}
