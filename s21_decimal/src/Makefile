.PHONY: all clean

CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

SOURCEDIR=./
BUILDDIR=build
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
HEADFILES=$(wildcard $(HEADERDIR)/*.h)
OBJFILES=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
EXECUTABLE=release.a


s21_decimal.a: clean dir $(EXECUTABLE)
	mv $(EXECUTABLE) s21_decimal.a

test:
	$(CC) $(CFLAGS) $(LDFLAGS) s21_other.c s21_mul.c s21_decimal.c s21_compare_decimal.c test_mablever.c

dir:
	mkdir $(BUILDDIR)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CCLDFLAGS) -o $@ $?

$(OBJFILES): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c $(HEADFILES)
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
		-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg gcov_main

gcov_report:
	$(CC) $(CFLAGS) $(LDFLAGS) $(GCOVFLAGS) *.c -o gcov_main
	./gcov_main
	gcov s21_*.gcno > report.html
	#lcov --capture --directory . --output-file coverage.info
	#genhtml coverage.info --output-directory gcov_report