
# SHELL macro
SHELL  := /bin/bash

# colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
RESET  := \033[0m

# name macro
NAME   := libwastewiz.a

# command macros
CC        := cc
AR        := ar rcs
RM        := rm -f
ADD_FLAGS := -g -fsanitize=address,undefined
CFLAGS    := #-Wall -Wextra -Werror

# VPATH
VPATH     := src

# src and obj files macros
SRC_PATH  := src
OBJ_PATH  := obj
SRC       := ww_area.c ww_free_func.c ww_obj.c ww_waste.c
OBJ       := $(SRC:%.c=$(OBJ_PATH)/%.o)

###################################
#	SYSTEM SPECIFIC SETTINGS	  #
###################################

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

###################################
#	RULES						  #
###################################

# file targets
$(NAME): $(OBJ_PATH) $(OBJ)
	@echo -e -n "$(BLUE)Creating: waste_wizard library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: waste_wizard success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile waste_wizard.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(FLAGS) $(ADD_FLAGS) -I. -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(RED)make: waste_wizard cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

