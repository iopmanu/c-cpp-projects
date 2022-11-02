.PHONY: all clean

CC=gcc
CFLAGS=-Wall -Wextra -pedantic

SOURCEDIR=./
BUILDDIR=build
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
HEADFILES=$(wildcard $(HEADERDIR)/*.h)
OBJFILES=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
EXECUTABLE=release


s21_cat: clean dir $(EXECUTABLE)
	mv $(EXECUTABLE) s21_cat

dir:
	mkdir $(BUILDDIR)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CFLAGS) $(CCLDFLAGS) -o $@ $?

$(OBJFILES): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c $(HEADFILES)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILDDIR) s21_cat

