CC=gcc
CFLAGS= -Wall -Wextra -pedantic -g -lm
LFLAGS ?= $(shell pkg-config --cflags --libs check)

SRC_DIR= .
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build

SRC  := $(shell find $(SRC_DIR) -name "s21*.c" | sed -e 's/\.\///')
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST=main.c
TEST_OBJS=$(BUILD_DIR)/tests/s21_tests.o

s21_smart_calc: clean s21_smart_calc.a test

test: s21_smart_calc.a $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) s21_smart_calc.a $(LFLAGS) -o smart_calc.out

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
	rm -rf smart_calc.out

codestyle:
	clang-format -i $(SRC)
