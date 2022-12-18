CC_FLAGS=-Wall -Wextra -Werror 
OS=$(shell uname -s)

ifeq ($(OS),Linux)
	TEST_FLAGS=-lcheck -pthread -lcheck_pic -pthread -lrt -lm -lsubunit
	CC_FLAGS+=-lm
else
	TEST_FLAGS=-lcheck
endif

all: s21_matrix.a

rebuild: clean all

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a
	rm -f *.o

s21_matrix.o:
	gcc -c $(CC_FLAGS) s21_matrix.c

test: clean s21_matrix.o
	gcc -c $(CC_FLAGS) s21_tests.c
	gcc $(CC_FLAGS) $(TEST_FLAGS) s21_tests.o s21_matrix.o -o tests.out 
	./tests.out

gcov_report: 
	gcc $(CC_FLAGS) --coverage -o make_report.out s21_tests.c s21_matrix.c $(TEST_FLAGS)
	./make_report.out
	lcov -t "make_report" -o make_report.info -c -d . 
	genhtml -o report make_report.info

style:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h

leaks: test
	CK_FORK=no leaks --atExit -- ./tests.out

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *cfg *.a
	rm -rf report/
	rm -rf temp/
