#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define short_options "e:ivclnhsf:o"
#define GET getopt_long(argc, argv, short_options, NULL, NULL)
#define REGEX regexec(&preg, str, 0, &pm, 0)

struct flags {
  int c, e, f, h, i, l, n, o, v, s, zero, many_files, c_counter, l_counter,
      n_counter, o_counter;
};

struct grep_char {
  size_t counter;
  char name[500][500];
};

void flag_finder(int c);
void file_hook(const char* file_name);
void pattern_copy(const char* string);
void s21_grep(int argc, char** argv);
void pattern_file_copy(const char* string);
void file_printer(FILE* file);
void error_printer();
void pattern_exe_extra(char* str);
void pattern_exe(char* str);
void print_file_name();
void printer_add();
size_t c_check(int c);

#endif  // SRC_GREP_S21_GREP_H_
