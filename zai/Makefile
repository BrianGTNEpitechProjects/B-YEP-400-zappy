##
## EPITECH PROJECT, 2018
## zappy_ai
## File description:
## Makefile for the project zappy_ai
##

NAME	=	zappy_ai

.PHONY: pre_build post_build target all clean fclean re
.DEFAULT_GOAL := all

pre_build:
		@printf "\n\e[33m[MAKE]\e[39m %s\n\n" $(NAME)

post_build:
		@printf "\e[33m[DONE]\e[39m\n\n"

all:		target

target:		pre_build $(NAME) post_build

$(NAME):
		cp sources/zappy_ai $(NAME)

clean:
		@printf "\n\e[33m[CLEAN]\e[39m\n\n"

fclean:		clean
		@printf "\n\e[33m[FCLEAN]\e[39m\n\n"
		$(RM) $(NAME)
		@printf "\e[31m[DELETE]\e[39m %s\n\n" $(NAME)
		@printf "\e[33m[DONE]\e[39m\n\n"

re:		fclean all
