.PHONY: all clean

CC=gcc
CFLAGS=-Wall -Wextra -Werror
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: s21_math.a

s21_math.a:
	$(CC) $(CFLAGS) -c s21_math.c
	ar rc s21_math.a *.o
	ranlib s21_math.a
	
clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt

test:
	$(CC) $(CFLAGS) $(LDFLAGS) s21_math.c tests/*.c

gcov_report:
	$(CC) $(CFLAGS) $(LDFLAGS) $(GCOVFLAGS) s21_math.c tests/*.c -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
