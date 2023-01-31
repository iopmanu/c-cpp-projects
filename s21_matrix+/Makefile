CC = g++
CFLAGS = -Wall -Wextra
SRC_DIR= src
TEST_DIR=tests
INCLUDE_DIR := $(shell find $(SRC_DIR) -type d)
BUILD_DIR=build

SRC  := $(shell find $(SRC_DIR)/code -name "s21*.cpp" | sed -e 's/\.\///')
INCLUDE := $(shell find $(SRC_DIR)/include -name "s21*.h" | sed -e 's/\.\///')
OBJS := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

all: clean s21_matrix_oop.a

tests: clean
	$(CC) $(CFLAGS) src/tests.cpp src/code/s21_matrix_oop.cpp -lgtest
	./a.out

s21_matrix_oop.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_matrix_oop.a $(OBJS)
	ranlib s21_matrix_oop.a

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

clean:
	rm -f s21_matrix_oop.a
	rm -rf $(BUILD_DIR)
	rm -Rf *.o *.out

codestyle:
	clang-format -i $(SRC_DIR)/include/* $(SRC_DIR)/code/*
