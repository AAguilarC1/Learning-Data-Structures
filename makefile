dbg ?= 0
NAME := Fibonacci-Heap
SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build
INCLUDE_DIR := include
TESTS_DIR := tests
BIN_DIR := bin

OBJS := $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/**/*.c))

CC := clang
CFLAGS := -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__ -Wall -Wextra -pedantic
LDFLAGS := -lm

LINTER := clang-tidy
FORMATTER := clang-format

ifeq ($(dbg), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

all: $(NAME)

$(OBJS): dir
	@mkdir -p $(BUILD_DIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ -c $*.c

$(NAME): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/$(NAME) $(addprefix $(BUILD_DIR)/, $(OBJS)) $(LDFLAGS) 

check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BIN_DIR)/$(NAME)

test: dir
	@$(CC) $(CFLAGS) -lcunit -o $(BIN_DIR)/$(NAME)_test $(TESTS_DIR)/*.c
	@$(BIN_DIR)/$(NAME)_test

# lint:
# 	@$(LINTER) --config-file=.clang-tidy $(SRC_DIR)/* $(INCLUDE_DIR)/* $(TESTS_DIR)/* -- $(CFLAGS)

# format:
# 	@$(FORMATTER) -style=file -i $(SRC_DIR)/* $(INCLUDE_DIR)/* $(TESTS_DIR)/*

setup:
	@sudo apt install -y valgrind clang-format clang-tidy
	@sudo apt install -y build-essential
	@sudo apt install -y libcunit1 libcunit1-doc libcunit1-dev
	@sudo apt update
	@sudo apt upgrade -y
	@sudo apt autoremove -y

dir:
	@mkdir -p $(BUILD_DIR)

run: all
	@./$(BIN_DIR)/$(NAME)

clean :
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: lint format check setup dir clean