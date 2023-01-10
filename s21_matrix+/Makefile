CC = g++
CFLAGS = -Wall -Wextra -pedantic
SRC_DIR= src
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build

SRC  := $(shell find $(SRC_DIR)/code -name "s21*.cpp" | sed -e 's/\.\///')
INCLUDE := $(shell find $(SRC_DIR)/include -name "s21*.h" | sed -e 's/\.\///')
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)

all: clean s21_matrix_oop.a

s21_matrix_oop.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_matrix_oop.a $(OBJS)
	ranlib s21_matrix_oop.a

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(CLFAGS) -c main.cpp -o $(BUILD_DIR)/main.o

clean:
	rm -f s21_matrix_oop.a
	rm -rf $(BUILD_DIR)

codestyle:
	clang-format -i $(SRC_DIR)/include/* $(SRC_DIR)/code/*
