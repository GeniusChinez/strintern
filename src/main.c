#include "intern.c"
#include <stdio.h>

int main(int argc, char**argv) {
  char* str1 = intern_string("first string");
  char* str2 = intern_string("first string");

  printf("%p %p %d\n", str1, str2, str1==str2);
  return 0;
}