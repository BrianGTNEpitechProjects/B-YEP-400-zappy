/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** graphical_protocol.h
*/

/* Created the 17/06/2019 at 16:40 by jfrabel */

#ifndef PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H
#define PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H

#include "zworld.h"
#include "zserver.h"

typedef struct graphical_user {
    zuser_ws_t base;
    zappy_t *world_infos;
} graphical_user_t;

typedef struct guser_possible_cmds {
    const char *cmd;
    bool (*func)(graphical_user_t *, network_client_t *, uint8_t *, size_t);
} guser_possible_cmds_t;

graphical_user_t *create_new_graphical_user(zappy_t *world_data);
void delete_graphical_user(graphical_user_t *user);

void update_ws_server(zappy_t *zap);

void send_to_all_ws_clients(zappy_t *world, uint8_t *msg, size_t len);

void handle_graphical_user_cmd(graphical_user_t *user,
    network_client_t *client, uint8_t *data, size_t data_size);

bool msz(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool bct(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool mct(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool tna(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool ppo(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool plv(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool pin(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool sgt(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool sst(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool suc(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool sbp(graphical_user_t *, network_client_t *, uint8_t *, size_t);

void smg(zappy_t *world, const char *msg);
void seg(zappy_t *world, const char *team);

#endif //PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H
