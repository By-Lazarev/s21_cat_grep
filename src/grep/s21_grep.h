#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define short_options "e:ivclnhsf:o"
#define GET getopt_long(argc, argv, short_options, NULL, NULL)
#define REGEX regexec(&preg, str, 0, pmatch, 0)
#define REG_EXT_NEW REG_EXTENDED|REG_NEWLINE
#define NO_FLAGS_L_V_C !flag.l && !flag.v && !flag.c

struct flags {
  int c, e, f, h, i, l, n, o, v, s, zero, many_files, c_counter, l_counter,
      n_counter, o_counter;
};

struct grep_char {
  size_t counter;
  char name[500][500];
};

void error_no_file_printer(const char* file_name);
void pattern_file_copy(const char* file_name);
void file_hook(const char* file_name);
void pattern_copy(const char* string);
void s21_grep(int argc, char** argv);
size_t flag_num_in_array(int c);
void file_printer(FILE* file);
void pattern_exe(char* str);
void flag_finder(int c);
void print_file_name();
void error_printer();
void printer_add();

#endif  // SRC_GREP_S21_GREP_H_
