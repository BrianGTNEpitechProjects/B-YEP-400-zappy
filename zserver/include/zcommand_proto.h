/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#ifndef PSU_ZAPPY_2018_ZCOMMAND_PROTO_H
#define PSU_ZAPPY_2018_ZCOMMAND_PROTO_H

#include "network_client_user_map.h"
#include "zitem.h"

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
typedef bool (*validation_func)(client_user_pair_t *, char *);

typedef struct {
    e_command_t code;
    char *command;
    int charge_time;
    bool need_arg;
    validation_func is_valid;
    command_func callback;
} command_info_t;

typedef struct command_s {
    e_command_t code;
    double remaining_time;
    char arg[ARG_BUFFER_SIZE];
} command_t;

typedef struct {
    int player_nb;
    unsigned int stones[TOT_ITEM_NB];
} incantation_requirement_t;


#endif //PSU_ZAPPY_2018_ZCOMMAND_PROTO_H
