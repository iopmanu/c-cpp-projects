CC = gcc
CFLAGS = -Wall -Wextra -pedantic
SRC_DIR= src
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build

SRC  := $(shell find $(SRC_DIR) -name "*.cpp" | sed -e 's/\.\///')
INCLUDE := $(shell find $(SRC_DIR) -name "*.h" | sed -e 's/\.\///')
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)

all: s21_matrix_oop.a

s21_matrix_oop.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_matrix_oop.a $(OBJS)
	ranlib s21_matrix_oop.a

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -f s21_matrix_oop.a
	rm -rf $(BUILD_DIR)

codestyle:
	clang-format -i $(SRC_DIR)/include/* $(SRC_DIR)/code/*
