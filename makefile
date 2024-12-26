dbg ?= 0
TARGET := Fibonacci-Heap
SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build
INCLUDE_DIR := ./include/
TESTS_DIR := tests
BIN_DIR := bin

OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

INCS := $(patsubst $(SRC_DIR)/%.c, -I$(INCLUDE_DIR), $(wildcard $(SRC_DIR)/*.c))

CC := gcc
CFLAGS := -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__ -Wall -Wextra -pedantic
LDFLAGS := -lm


ifeq ($(dbg), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

all: dir $(TARGET)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BIN_DIR)/$(TARGET)

test: 
	@$(CC) $(CFLAGS) -lcunit -o $(BIN_DIR)/$(TARGET)_test $(TESTS_DIR)/*.c
	@$(BIN_DIR)/$(TARGET)_test

setup:
	@sudo apt install -y valgrind 

dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

run: all
	@./$(BIN_DIR)/$(TARGET)

clean :
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: check setup dir clean