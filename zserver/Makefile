##
## EPITECH PROJECT, 2018
## zappy_server
## File description:
## Makefile for the project zappy_server
##

SRC_DIR		=	$(realpath sources)

SRC_FILES	=	\
				main.c \
				utils.c \
				global.c \
				gameplay/zappy.c \
				gameplay/zappy_run.c \
				gameplay/on_extract_connected.c \
				gameplay/map.c \
				gameplay/server_running.c \
				gameplay/arguments.c \
				gameplay/connection.c \
				gameplay/teams.c \
				gameplay/trantorian/new.c \
				gameplay/process_command.c \
				gameplay/trantorian/move.c \
				gameplay/trantorian/tile.c \
				gameplay/trantorian/neighbour.c \
				gameplay/utils/cardinal_utils.c \
				gameplay/utils/always_true.c \
				gameplay/utils/get_item_id_from_name.c \
				gameplay/utils/kill_client.c \
				gameplay/utils/set_to_next_command.c \
				gameplay/utils/apply_time.c \
				websockets/websocket.c \
				websockets/websocket_header_end.c \
				websockets/websocket_header_start.c \
				websockets/websocket_set_connection.c \
				websockets/websocket_set_key.c \
				websockets/websocket_set_upgrade.c \
				graphical_protocol/graphical_user.c \
				graphical_protocol/handle_graphical_user_cmd.c \
				graphical_protocol/update_ws_server.c \
				base64.c

COMMAND_DIR		=	$(realpath sources/gameplay/commands)

COMMAND_FILES	=	\
					forward.c\
					eject.c\
					right.c\
					left.c\
					look.c\
					inventory.c\
					broadcast.c\
					connect_nbr.c\
					put_object.c\
					take_object.c\
					incantation.c\
					fork.c\
					hatch_egg.c\

GCOMMAND_DIR	=	$(realpath sources/graphical_protocol/commands)

GCOMMAND_FILES	=	\
					bct.c \
					ebo.c \
					edi.c \
					eht.c \
					enw.c \
					mct.c \
					msz.c \
					pbc.c \
					pdi.c \
					pdr.c \
					pex.c \
					pfk.c \
					pgt.c \
					pic.c \
					pie.c \
					pin.c \
					plv.c \
					pnw.c \
					ppo.c \
					seg.c \
					sgt.c \
					smg.c \
					spb.c \
					sst.c \
					suc.c \
					tna.c

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
				network_manager_alloc.c \
				network_manager_servers_handle.c \
				network_manager_update.c \
				network_server_accept_connections.c \
				network_server_alloc.c \
				network_server_disconnect.c \
				network_server_extract.c \
				network_server_sync_buffer.c \
				network_server_update.c \

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES)) $(addprefix $(NETWORK_DIR)/, $(SRC_NETWORK)) $(addprefix $(COMMAND_DIR)/, $(COMMAND_FILES)) $(addprefix $(GCOMMAND_DIR)/, $(GCOMMAND_FILES))

OBJ			=	$(SRC:%.c=%.o)

NAME		=	zappy_server

LIB_CONTAINER_PATH	=	$(realpath lib/containers)
LIB_CONTAINER	=	$(addprefix $(LIB_CONTAINER_PATH)/, libcontainers.a)

LIB_C_BUFFER_PATH	=	$(realpath lib/circular_buffer)
LIB_C_BUFFER	=	$(addprefix $(LIB_C_BUFFER_PATH)/, libcircular_buffer.a)

INCLUDE		=	-iquote $(realpath include) -iquote $(realpath lib/containers/include) -iquote $(realpath lib/circular_buffer/include)

CFLAGS		=	-W -Wall -Wextra -Wno-unknown-pragmas -Wshadow
CFLAGS		+=	$(INCLUDE)

LDFLAGS		=	-L $(LIB_CONTAINER_PATH) -lcontainers -L $(LIB_C_BUFFER_PATH) -lcircular_buffer -lcrypto -lm

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

debug:		CFLAGS += -g -DGRAPHICAL_SERVER_DEBUG
debug:		re

tests_run:
			@$(MAKE) -C $(TESTS_DIR) && ./tests/test

tests_clean:
			@$(MAKE) -C $(TESTS_DIR) clean

tests_fclean:
			@$(MAKE) -C $(TESTS_DIR) fclean
