
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -lm
LFLAGS ?= $(shell pkg-config --cflags --libs check)
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR= .
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build
GCOV_DIR=gcov_report
DOC_DIR=html

SRC  := $(shell find $(SRC_DIR) -name "*.c" | sed -e 's/\.\///')
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST=
TEST_OBJS=$(BUILD_DIR)/tests/tests.o

all: clean

QT_PROJECT_NAME = qt
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = build
QT_APP_FOLDER = ../App
DIST_FOLDER_NAME = 3DViewer-v1.0

generate_make:
	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	@rm -rf .qmake.stash

install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir ./$(QT_APP_FOLDER)
ifeq ($(OS), Darwin)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/SmartCalc ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME).app
else
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
endif
	@echo " Done."
	@echo -n "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo " Done."
	@echo "Installation complete!"

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo " Done."

tests:  s21_lib.a $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) s21_lib.a $(LFLAGS) -o s21_test.out
	./s21_test.out

s21_lib.a: clean $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_lib.a $(OBJS)
	ranlib s21_lib.a

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

gcov_report: clean
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(SRC) $(LFLAGS) -o gcov.out
	./gcov.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open $(GCOV_DIR)/index.html
	rm -Rf *.gcda *.cov *.gcno *.info

TAR_DIR = SmartCalc_v1.0_v1.0_Archive

dist:
	rm -Rf $(TAR_DIR)
	mkdir $(TAR_DIR)
	mkdir $(TAR_DIR)/src
	cp $(SRC) qt/* $(TAR_DIR)/src
	tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
	mv $(TAR_DIR).tgz ..
	rm -Rf $(TAR_DIR)

dvi:
	doxygen Doxyfile
	open html/index.html

clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f s21_lib.a
	rm -rf $(BUILD_DIR) $(GCOV_DIR)
	rm -rf *out *info build*
	rm -rf $(DOC_DIR) $(TAR_DIR) ../$(TAR_DIR).tgz
codestyle:
	clang-format -i $(SRC)
