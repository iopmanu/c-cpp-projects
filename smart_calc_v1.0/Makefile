CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -lm
LFLAGS ?= $(shell pkg-config --cflags --libs check)
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR= .
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build

SRC  := $(shell find $(SRC_DIR) -name "s21*.c" | sed -e 's/\.\///')
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST=main.c
TEST_OBJS=$(BUILD_DIR)/tests/s21_tests.o

all: clean s21_smart_calc.a tests

tests: s21_test.out

s21_test.out: s21_smart_calc.a $(TEST_OBJS)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(TEST_OBJS) s21_smart_calc.a $(LFLAGS) -o s21_test.out

gcov_report: s21_test.out
	./s21_test.out
	lcov -t "s21_test.out" -c -d . -o gcovreport.info
	genhtml gcovreport.info -o report
	open -a report/index.html

s21_smart_calc.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_smart_calc.a $(OBJS)
	ranlib s21_smart_calc.a

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CLFAGS) -c main.c -o $(BUILD_DIR)/main.o

clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f s21_smart_calc.a
	rm -rf $(BUILD_DIR)
	rm -rf *out *info

codestyle:
	clang-format -i $(SRC)
