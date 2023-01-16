.PHONY: all clean

CC=gcc
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: s21_string.a

s21_string.a:
	$(CC) $(CFLAGS) -c *.c
	ar rc s21_string.a *.o
	ranlib s21_string.a
	
clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt gcov_main

test:
	$(CC) $(CFLAGS) $(LDFLAGS) *.c tests/*.c

gcov_report:
	$(CC) $(CFLAGS) $(LDFLAGS) $(GCOVFLAGS) *.c tests/*.c -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
