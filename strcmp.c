#include <stdio.h>
#include <assert.h>
#include <string.h>

char* build_string(dict* end, dict* prev, dict* start, char* str)

int main(void)
{
    char * str1 = "car";
    char * str1 = "part";

    char* build_string(dict* end, dict* prev, dict* start, char* str)

}


    printf("%d\n", strcmp("car", "part"));
    // assert(strcmp("car", "cart") == -1);
    // assert(strcmp("car", "part") == -7);
    return 0;
}

char* build_string(dict* end, dict* start, char* str)
{
   int pos = -1;
   int strpos = 0;
   char c;
   dict* prev;
   // recursive
   while (end != start) {
      prev = end;
      end = end->up;
      // find character index in node below
      for (int i = 0; i < ALPHA; i++) {
         if (end->dwn[i] == prev) {
            pos = i;
         }
      }
      if ((c = ind_to_char(pos)) != -1) {
         str[strpos++] = c;
      }
   }
   printf("%s", str);
   return str;
}