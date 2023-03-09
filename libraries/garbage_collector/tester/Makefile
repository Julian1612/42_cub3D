
# SHELL macro
SHELL  := /bin/bash

# colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
RESET  := \033[0m

# name macro
NAME   := tester

# src
SRC    := test.c

# lib macro
LIB_PATH := ../
LIB_NAME := wastewiz
LIB_LINK := -L$(LIB_PATH) -l$(LIB_NAME)
LIB_INC  := -I$(LIB_PATH)


# command macros
CC        := cc
RM        := rm -f
ADD_FLAGS := -g -fsanitize=address,undefined
CFLAGS    := #-Wall -Wextra -Werror

# VPATH
VPATH     := src

.PHONY: all clean

all:
	$(MAKE) -C $(LIB_PATH)
	$(CC) $(FLAGS) $(ADD_FLAGS) $(SRC) $(LIB_INC) $(LIB_LINK) -o $(NAME)
	@echo -e "$(YELLOW)Running test: $(RESET)"
	@echo
	@./$(NAME) | cat -e > out

#@valgrind --leak-check=full ./$(NAME) | cat -e

clean:
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_PATH) fclean
