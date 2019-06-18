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
#include "zcommand_proto.h"
#include "zposition.h"
#include "zworld.h"

#define COMMAND_NB (12)

extern const uint8_t OK_MSG[];
extern const size_t OK_MSG_LEN;
extern const uint8_t KO_MSG[];
extern const size_t KO_MSG_LEN;
extern const uint8_t WELCOME_MSG[];
extern const size_t WELCOME_MSG_LEN;

extern const command_info_t commands[];

/* commands (commands folder) */
void forward        (client_user_pair_t *client, char *arg);
void right          (client_user_pair_t *client, char *arg);
void left           (client_user_pair_t *client, char *arg);
void eject          (client_user_pair_t *client, char *arg);
void look           (client_user_pair_t *client, char *arg);
void inventory      (client_user_pair_t *client, char *arg);
void connect_nbr    (client_user_pair_t *client, char *arg);
void broadcast      (client_user_pair_t *client, char *arg);
void put_object     (client_user_pair_t *client, char *arg);
void take_object    (client_user_pair_t *client, char *arg);
void incantation    (client_user_pair_t *client, char *arg);
void fork_command(client_user_pair_t *client, char *arg);

/* --- utils --- */
/* utils/always_true.c */
bool always_true(client_user_pair_t *c, char *a);

/* look.c */
tile_t *top_left_corner_tile_at(tile_t *, e_cardinal_t, unsigned int);
int tile_look_limit(unsigned int lvl);


#endif //PSU_ZAPPY_2018_ZCOMMANDS_H
