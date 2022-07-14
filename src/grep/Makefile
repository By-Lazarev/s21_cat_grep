CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
.PHONY: clean all s21_grep

all: clean s21_grep test

test: clean s21_grep cpp
	./test_grep
	./t_grep
	./t_grep_memory

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.a *.out *.txt s21_grep

cpp:
	cp ../CPPLINT.cfg ./
	python3 ../cpplint.py --extensions=c *.c
	rm CPPLINT.cfg
	cppcheck --enable=all s21_grep.c s21_grep.h 

git: 
	git add .
	git commit -m'fast push from grep'
	git push origin develop

brew:
	git clone https://github.com/Homebrew/brew ~/goinfre/homebrew
	~/goinfre/homebrew/bin/brew install gcovr
	eval "$(~/goinfre/homebrew/bin/brew shellenv)"
	chmod -R go-w "$(brew --prefix)/bin/brew"

valgrind: s21_grep
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_grep aboba test/1
#	CK_FORK=no leaks --atExit -- ./s21_grep qwe 1.txt
