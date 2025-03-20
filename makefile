NAME := Data_Structures

SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build
INCLUDE_DIR := ./include/
TESTS_DIR := tests
BIN_DIR := bin

dbg ?= 0

SRC := $(wildcard $(SRC_DIR)/*.c)

OBJS :=  $(SRC:src/%.c=build/%.o)

TESTS := $(wildcard $(TESTS_DIR)/*.c)

INCS := $(patsubst $(SRC_DIR)/%.c, -I$(INCLUDE_DIR), $(wildcard $(SRC_DIR)/*.c))

# CC := gcc
CC := clang
CFLAGS := -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__ -Wall -Wextra -pedantic -Wno-int-conversion -Wno-incompatible-function-pointer-types
LDFLAGS := -lm

TARGET := $(BIN_DIR)/$(NAME).out
TEST := $(BIN_DIR)/$(NAME)_test.out

sanitize ?= 0

ifeq ($(dbg), 1)
	CFLAGS += -g -O0	
else
	CFLAGS += -O3
endif

ifeq ($(sanitize), 1)
	CFLAGS += -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address -fsanitize=undefined
endif

dirs : 
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(TARGET) : $(OBJS) 
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) $^ -o $@ $(LDFLAGS)

$(TEST): $(OBJS) 
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I./tests/include/ $(filter-out build/main.o, $(OBJS)) $(TESTS) -lcunit -o $@ $(LDFLAGS) 

all: build $(TARGET)

build: dirs $(OBJS)

check: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(TARGET)

profile: all
	valgrind --tool=massif --verbose --massif-out-file=./bin/massif.out $(TARGET)
	valgrind --tool=cachegrind --cachegrind-out-file=./bin/cachegrind.out $(TARGET)
	valgrind --tool=callgrind --callgrind-out-file=./bin/callgrind.out $(TARGET)

test: build $(TEST)
	@./${TEST}

setup:
	@sudo apt install -y valgrind 
	@sudo apt install -y libcunit1 libcunit1-dev libcunit1-doc

dir:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

run: all
	@./$(TARGET)

clean :
	rm -rf $(BUILD_DIR) $(BIN_DIR)


.PHONY: all build check clean setup update_tags

