#pragma once

#include <assert.h>
#include <string.h>

#include "alloca/src/alloc.c"
#include "intern.h"

void* __string_intern_table__[1024];
size_t __size_of_string_intern_table__ = 0;

char* intern_string_range(char* input_string_beginning, char* input_string_end) {
  int intern_table_index = 0;
  char* input_string_iterator;

  while (intern_table_index < __size_of_string_intern_table__) {
    char* intern_table_string_iterator = __string_intern_table__[intern_table_index];
    input_string_iterator = input_string_beginning;

    // check if the strings are the same
    while (
         (*input_string_iterator != 0)
      && (*intern_table_string_iterator != 0)
      && (*input_string_iterator == *intern_table_string_iterator)
    ) {
      input_string_iterator++;
      intern_table_string_iterator++;
    }

    if (
         (*input_string_iterator == *intern_table_string_iterator)
      && (*input_string_iterator == 0)
    ) {
      // the string already exists
      return __string_intern_table__[intern_table_index];
    }

    intern_table_index++;
  }

  assert(__size_of_string_intern_table__ < 1024);

  // the string doesnt exist, so create it and insert into table
  char* new_string = xcalloc(input_string_end - input_string_beginning + 1, sizeof(char));
  strncpy(new_string, input_string_beginning, input_string_end - input_string_beginning);
  __string_intern_table__[__size_of_string_intern_table__++] = new_string;

  return new_string;
}

char* intern_string(char* string_value) {
  char* end_of_string = string_value + strlen(string_value);
  return intern_string_range(string_value, end_of_string);
}

void clear_string_intern_table() {
  size_t intern_table_index = 0;
  while (intern_table_index < __size_of_string_intern_table__) {
    xfree(__string_intern_table__[intern_table_index++]);
  }
}