.PHONY: all clean

CC=gcc
CFLAGS=-Wall -Wextra -Wall -g
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: clean s21_decimal.a

s21_decimal.a:
	$(CC) $(CFLAGS) -c *.c
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
 
clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt gcov_main

main:
	$(CC) $(CFLAGS) $(LDFLAGS) *.c

test:
	$(CC) $(CFLAGS) $(LDFLAGS) *.c tests/test_mablever.c
	./a.out

gcov_report:
	$(CC) $(CFLAGS) $(LDFLAGS) $(GCOVFLAGS) *.c tests/test_mablever.c -o gcov_main
	./gcov_main
	gcov s21_*.gcno > report.html
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

