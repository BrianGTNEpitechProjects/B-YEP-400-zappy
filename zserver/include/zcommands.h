/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#ifndef PSU_ZAPPY_2018_ZCOMMANDS_H
#define PSU_ZAPPY_2018_ZCOMMANDS_H

#include "network_client_user_map.h"
#include "circular_buffer.h"

#define ARG_BUFFER_SIZE C_BUFFER_SIZE

typedef enum {
    EMPTY,
    FORWARD,
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    CONNECT_NBR,
    FORK,
    EJECT,
    TAKE_OBJECT,
    SET_OBJECT,
    INCANTATION
} e_command_t;

typedef void (*command_func)(client_user_pair_t *, char *);

typedef struct {
    e_command_t code;
    char *command;
    command_func callback;
} command_info_t;

typedef struct {
    e_command_t code;
    char arg[ARG_BUFFER_SIZE];
} command_t;

extern const command_info_t commands[];

/* commands (commands folder) */
void forward(client_user_pair_t *client, char *arg);

#endif //PSU_ZAPPY_2018_ZCOMMANDS_H
