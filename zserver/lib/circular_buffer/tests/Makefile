##
## EPITECH PROJECT, 2018
## library circular_buffer tests
## File description:
## Makefile for the tests of the library circular_buffer
##

SRC_DIR		=	$(realpath ../sources)

SRC_FILES	=	\
				circular_buffer_clear.c \
				circular_buffer_flush.c \
				circular_buffer_read.c \
				circular_buffer_read_bytes.c \
				circular_buffer_write.c \

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

TEST_DIR	=	$(realpath ./sources)

TEST_FILES	=	$(addprefix tests_, $(SRC_FILES))

TEST_SRC	=	$(addprefix $(TEST_DIR)/, $(TEST_FILES))

OBJ			=	$(SRC:%.c=%.o) $(TEST_SRC:%.c=%.o)

NAME		=	test

INCLUDE		=	-iquote $(realpath ../include)

CFLAGS		=	-W -Wall -Wextra -Werror -Wno-unknown-pragmas
CFLAGS		+=	$(INCLUDE)

LDFLAGS		=	-lcriterion

CC			=	gcc

RM			=	rm -rf

.PHONY: pre_build post_build target all clean fclean re debug
.DEFAULT_GOAL := all

%.o:		%.c
			@echo "\e[34m[COMPILATION]\e[39m $<\c"
			@$(CC) -o $@ -c $< $(CFLAGS)
			@echo " => \e[32mOK\e[39m"

pre_build:
			@echo "\e[35m[MAKE]\e[39m $(NAME)"

post_build:
			@echo "\e[35m[DONE]\e[39m"

all:		target

target:		pre_build $(NAME) post_build

$(NAME):	$(OBJ)
			@echo "\e[34m[LINKING]\e[39m $@\c"
			@$(CC) -o $@ $(OBJ) $(LDFLAGS)
			@echo " => \e[32mOK\e[39m"

clean:
			@echo "\e[33m[CLEAN]\e[39m $(OBJ)\c"
			@$(RM) $(OBJ)
			@echo " => \e[32mOK\e[39m"

fclean:		clean
			@echo "\e[33m[CLEAN]\e[39m $(NAME)\c"
			@$(RM) $(NAME)
			@echo " => \e[32mOK\e[39m"

re:			fclean all

debug:		CFLAGS += -g
debug:		re