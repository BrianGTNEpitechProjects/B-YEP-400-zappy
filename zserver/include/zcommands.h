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

extern const uint8_t OK_MSG[];
extern const size_t OK_MSG_LEN;
extern const uint8_t KO_MSG[];
extern const size_t KO_MSG_LEN;
extern const uint8_t WELCOME_MSG[];
extern const size_t WELCOME_MSG_LEN;

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
    validation_func is_valid;
    command_func callback;
} command_info_t;

typedef struct {
    e_command_t code;
    double remaining_time;
    char arg[ARG_BUFFER_SIZE];
} command_t;

extern const command_info_t commands[];

/* commands (commands folder) */
void forward(client_user_pair_t *client, char *arg);
void right(client_user_pair_t *client, char *arg);
void left(client_user_pair_t *client, char *arg);
void eject(client_user_pair_t *client, char *arg);
void look(client_user_pair_t *c, char *arg);
void inventory(client_user_pair_t *client, char *arg);
void connect_nbr(client_user_pair_t *client, char *arg);

/* utils/always_true.c */
bool always_true(client_user_pair_t *c, char *a);

#endif //PSU_ZAPPY_2018_ZCOMMANDS_H
