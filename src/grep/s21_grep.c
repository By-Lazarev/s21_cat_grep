#include "s21_grep.h"

/* 
  FAILED:
  s21_grep reflect 10_1.file 10_2.file
  s21_grep -i trulyalya 11.file
  s21_grep -v s 12.file
  s21_grep -c s 13.file
  s21_grep -n s 15.file
  s21_grep -o 123 16.file
  s21_grep -h reflect 17_1.file 17_2.file
  s21_grep -f 19_1.file 19_2.file
*/

struct flags flag = {0};
struct grep_char s21_pattern = {0};
struct grep_char s21_file = {0};

void s21_grep(int argc, char** argv) {
  if (argc < 3) error_printer();
  s21_pattern.counter = s21_file.counter = 0;
  for (int c = GET; c != -1; c = GET) flag_finder(c);
  if (!flag.e && !flag.f) pattern_copy(argv[optind++]);
  flag.many_files = argc - optind;
  while (optind < argc) file_hook(argv[optind++]);
}

void flag_finder(int c) {
  if (c == '?') error_printer();
  *(&flag.c + c_check(c)) = 1;
  if (c == 'e') pattern_copy(optarg);
  if (c == 'f') pattern_file_copy(optarg);
}

size_t c_check(int c) {
  size_t res = 0;
  for (char* str = "cefhilnovs"; str[res] != (char)c; res++) {}
  return res;
}

void pattern_copy(const char* string) {
  strcpy(s21_pattern.name[s21_pattern.counter++], string);
}

void pattern_file_copy(const char* string) {
  FILE* file = fopen(string, "r");
  if (file) {
    for (char c = getc(file); c != EOF && !feof(file);
         s21_pattern.counter++, c = getc(file)) {
      size_t pos = 0;
      s21_pattern.name[s21_pattern.counter][pos] = c;
      for (; c != EOF && c != '\n' && !feof(file);
           s21_pattern.name[s21_pattern.counter][pos++] = c, c = getc(file)) {
      }
    }
    fclose(file);
  } else {
    printf("\n>%s:\tФайл не найден или вы ошиблись при вводе.\n", string);
  }
}

void file_hook(const char* file_name) {
  FILE* file = fopen(file_name, "r");
  if (file) {
    strcpy(s21_file.name[s21_file.counter++], file_name);
    file_printer(file);
    fclose(file);
  } else if (!flag.s) {
    printf("\n>%s:\tФайл не найден или вы ошиблись при вводе.\n", file_name);
  }
}

void file_printer(FILE* file) {
  char str[500] = "";
  size_t pos = 0;
  flag.c_counter = flag.l_counter = flag.n_counter = 0;
  for (char c = getc(file); c != EOF && !feof(file); c = getc(file)) {
    flag.n_counter++;
    pos = 0;
    str[pos] = c;
    for (; c != EOF && c != '\n' && !feof(file);
         str[pos++] = c, c = getc(file)) {
    }
    str[pos] = '\0';
    if (flag.o && !flag.v && !flag.c && !flag.l) {
      pattern_exe_extra(str);
      flag.zero = 1;
    } else {
      pattern_exe(str);
    }
    if (flag.l_counter == 1) break;
  }
  if (!flag.zero) printer_add();
}

void pattern_exe(char* str) {
  size_t res = 0;
  flag.o_counter = 0;
  regex_t preg = {0};
  regmatch_t pm = {0};
  for (size_t current_pattern = 0; current_pattern < s21_pattern.counter;
       current_pattern++) {
    regcomp(&preg, s21_pattern.name[current_pattern],
            flag.i ? REG_NEWLINE|REG_ICASE|REG_EXTENDED : REG_EXTENDED);

    if (REGEX == flag.v) res++;
    regfree(&preg);
  }
  if (res == s21_pattern.counter || (res && !flag.v)) {
    if (flag.c) flag.c_counter++;
    if (flag.l) flag.l_counter = 1;
    if (!flag.c && !flag.l) {
      print_file_name();
      if (flag.n) printf("%d:", flag.n_counter);
      printf("%s\n", str);
    }
  }
}

void pattern_exe_extra(char* str) {
  size_t first_file = 0, first_num = 0;
  regex_t     preg = {0};
  regmatch_t  pmatch[1] = {0};
  for (size_t current_pattern = 0; current_pattern < s21_pattern.counter;
        current_pattern++) {
    regcomp(&preg, s21_pattern.name[current_pattern],
            flag.i ? REG_NEWLINE|REG_ICASE|REG_EXTENDED : REG_NEWLINE|REG_EXTENDED);

    while (!regexec(&preg, str, 1, pmatch, 0)) {
      if (first_file++ == 0) print_file_name();
      if (flag.n && first_num++ == 0) printf("%d:", flag.n_counter);
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so), str + pmatch[0].rm_so);
      str += pmatch[0].rm_eo;
    }
    regfree(&preg);
    }
}

void printer_add() {
  if (flag.c) {
    print_file_name();
    printf("%d\n", flag.c_counter);
  }
  if (flag.l && flag.l_counter)
    printf("%s\n", s21_file.name[s21_file.counter - 1]);
}

void print_file_name() {
  if (flag.many_files > 1 && !flag.h)
    printf("%s:", s21_file.name[s21_file.counter - 1]);
}

void error_printer() {
  system("clear");
  if (!flag.s)
    printf(
        ">\tПожалуйста укажите файл для запуска. И верно используйте "
        "флаги\n./s21_grep [-options] [\"pattern\"] [\"file.name\"]");
  exit(0);
}

int main(int argc, char** argv) {
  s21_grep(argc, argv);
  return 0;
}
