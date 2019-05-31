##
## EPITECH PROJECT, 2018
## zappy_server
## File description:
## Makefile for the project zappy_server
##

SRC_DIR		=	$(realpath sources)

SRC_FILES	=	\
				main.c

NETWORK_DIR	=	$(realpath sources/network)

SRC_NETWORK	=	\
				global.c \
				network_client_compare.c \
				network_client_flush.c \
				network_client_pool_getters.c \
				network_client_pool_infos.c \
				network_client_pool_manage.c \
				network_client_user_map_getters.c \
				network_client_user_map_manage.c \
				network_client_user_map_without_users.c \
				network_manager_accept_connections.c \
				network_manager_alloc.c \
				network_manager_disconnect.c \
				network_manager_extract.c \
				network_manager_sync_buffer.c \
				network_manager_update.c \

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES)) $(addprefix $(NETWORK_DIR)/, $(SRC_NETWORK))

OBJ			=	$(SRC:%.c=%.o)

NAME		=	zappy_server

LIB_CONTAINER_PATH	=	$(realpath lib/containers)
LIB_CONTAINER	=	$(addprefix $(LIB_CONTAINER_PATH)/, libcontainers.a)

LIB_C_BUFFER_PATH	=	$(realpath lib/circular_buffer)
LIB_C_BUFFER	=	$(addprefix $(LIB_C_BUFFER_PATH)/, libcircular_buffer.a)

INCLUDE		=	-iquote $(realpath include) -iquote $(realpath lib/containers/include) -iquote $(realpath lib/circular_buffer/include)

CFLAGS		=	-W -Wall -Wextra -Werror -Wno-unknown-pragmas -Wshadow
CFLAGS		+=	$(INCLUDE)

LDFLAGS		=	-L $(LIB_CONTAINER_PATH) -lcontainers -L $(LIB_C_BUFFER_PATH) -lcircular_buffer

TESTS_DIR	=	$(realpath tests)

CC			=	gcc

RM			=	rm -rf

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

$(LIB_CONTAINER):
			$(MAKE) -C $(LIB_CONTAINER_PATH)

$(LIB_C_BUFFER):
			$(MAKE) -C $(LIB_C_BUFFER_PATH)

$(NAME):	$(OBJ) $(LIB_CONTAINER) $(LIB_C_BUFFER)
			@printf "\n\e[34m[LINKING]\e[39m $@"
			@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
			@printf " => \e[32mOK\e[39m\n\n"

clean:
			$(MAKE) -C $(LIB_CONTAINER_PATH) clean
			$(MAKE) -C $(LIB_C_BUFFER_PATH) clean
			@printf "\n\e[33m[CLEAN]\e[39m\n\n"
			@$(RM) $(OBJ)
			@printf "\e[31m[DELETE]\e[39m %s\n" $(OBJ)
			@printf "\n"
			@printf "\e[33m[DONE]\e[39m\n\n"

fclean:		clean
			$(MAKE) -C $(LIB_CONTAINER_PATH) fclean
			$(MAKE) -C $(LIB_C_BUFFER_PATH) fclean
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