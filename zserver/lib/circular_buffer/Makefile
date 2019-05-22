##
## EPITECH PROJECT, 2018
## libcircular_buffer
## File description:
## Makefile for the project libcircular_buffer
##

SRC_DIR		=	$(realpath sources)

SRC_FILES	=	\
				circular_buffer_clear.c \
				circular_buffer_flush.c \
				circular_buffer_read.c \
				circular_buffer_read_bytes.c \
				circular_buffer_write.c \

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ			=	$(SRC:%.c=%.o)

NAME		=	libcircular_buffer.a

INCLUDE		=	-iquote $(realpath include)

CFLAGS		=	-W -Wall -Wextra -Werror -Wno-unknown-pragmas
CFLAGS		+=	$(INCLUDE)

LDFLAGS		=

TESTS_DIR	=	$(realpath tests)

CC			=	gcc

RM			=	rm -rf

AR			=	ar rc

.PHONY: pre_build post_build target all clean fclean re debug
.DEFAULT_GOAL := all

%.o:		%.c
			@printf "\e[34m[COMPILATION]\e[39m %s" $<
			@$(CC) -o $@ -c $< $(CFLAGS)
			@printf " => \e[32mOK\e[39m\n"

pre_build:
			@printf "\n\e[33m[MAKE]\e[39m $(NAME)\n\n"

post_build:
			@printf "\e[33m[DONE]\e[39m\n\n"

all:		target

target:		pre_build $(NAME) post_build

$(NAME):	$(OBJ)
			@printf "\n\e[34m[LINKING]\e[39m $@"
			@$(AR) $@ $(OBJ)
			@printf " => \e[32mOK\e[39m\n\n"

clean:
			@printf "\n\e[33m[CLEAN]\e[39m\n\n"
			@$(RM) $(OBJ)
			@printf "\e[31m[DELETE]\e[39m %s\n" $(OBJ)
			@printf "\n"
			@printf "\e[33m[DONE]\e[39m\n\n"

fclean:		clean
			@echo "\n\e[33m[FCLEAN]\e[39m\n"
			@$(RM) $(NAME)
			@printf "\e[31m[DELETE]\e[39m %s\n\n" $(NAME)
			@printf "\e[33m[DONE]\e[39m\n\n"

re:			fclean all

debug:		CFLAGS += -g
debug:		re

tests_run:
			@$(MAKE) -C $(TESTS_DIR) && ./tests/test

tests_clean:
			@$(MAKE) -C $(TESTS_DIR) clean

tests_fclean:
			@$(MAKE) -C $(TESTS_DIR) fclean