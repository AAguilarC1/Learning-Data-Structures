dbg ?= 0
NAME := Fibonacci-Heap
SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build
INCLUDE_DIR := include
TESTS_DIR := tests
BIN_DIR := bin

OBJS := $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c))

CC := gcc
CFLAGS := -std=gnu17 -D _GNU_SOURCE -D __STDC_WANT_LIB_EXT1__ -Wall -Wextra -pedantic
LDFLAGS := -lm


ifeq ($(dbg), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

all: $(NAME)

$(OBJS): dir
	@mkdir -p $(BUILD_DIR)/$(@D)
	@$(CC) $(CFLAGS) $(INC) -o $(BUILD_DIR)/$@ -c $*.c

$(NAME): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(NAME) $(addprefix $(BUILD_DIR)/, $(OBJS)) $(LDFLAGS) $(INC)

check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BIN_DIR)/$(NAME)

test: dir
	@$(CC) $(CFLAGS) -lcunit -o $(BIN_DIR)/$(NAME)_test $(TESTS_DIR)/*.c
	@$(BIN_DIR)/$(NAME)_test

setup:
	@sudo apt install -y valgrind 

dir:
	@mkdir -p $(BUILD_DIR)

run: all
	@./$(BIN_DIR)/$(NAME)

clean :
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: check setup dir clean