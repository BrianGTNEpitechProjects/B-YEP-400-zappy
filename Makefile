##
## EPITECH PROJECT, 2018
## zappy
## File description:
## Makefile for the project zappy
##

ZAPPY_SERVER_PATH	=	$(realpath zserver)

ZAPPY_SERVER	=	zappy_server

ZAPPY_AI_PATH	=	$(realpath zai)

ZAPPY_AI	=	zappy_ai

CP	=	cp

RM	=	rm -rf

all:	$(ZAPPY_SERVER) $(ZAPPY_AI)

$(ZAPPY_AI):
		$(MAKE) -C $(ZAPPY_AI_PATH)
		$(CP) $(ZAPPY_AI_PATH)/$(ZAPPY_AI) . || echo "\e[31m[ERROR] Could not find zappy_ai binary\e[39m"

$(ZAPPY_SERVER):
		$(MAKE) -C $(ZAPPY_SERVER_PATH)
		$(CP) $(ZAPPY_SERVER_PATH)/$(ZAPPY_SERVER) . || echo "\e[31m[ERROR] Could not find zappy_server binary\e[39m"

clean:
		$(MAKE) -C $(ZAPPY_SERVER_PATH) clean
		$(MAKE) -C $(ZAPPY_AI_PATH) clean

fclean:	clean
		$(MAKE) -C $(ZAPPY_SERVER_PATH) fclean
		$(MAKE) -C $(ZAPPY_AI_PATH) fclean
		$(RM) $(ZAPPY_SERVER)
		$(RM) $(ZAPPY_AI)

re:		fclean all