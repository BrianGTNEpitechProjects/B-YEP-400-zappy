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

graphical_user_t *create_new_graphical_user(zappy_t *world_data);
void delete_graphical_user(graphical_user_t *user);

void update_ws_server(zappy_t *zap);

#endif //PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H
