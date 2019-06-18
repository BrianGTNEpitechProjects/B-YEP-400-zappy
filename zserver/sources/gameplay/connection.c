/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** connection.c
*/

#include <string.h>
#include "zserver.h"
#include "zworld.h"

trantorian_t *get_egg_hatched(const char *team, zappy_t *zap)
{
    for (trantorian_t *curr = zap->players; curr != NULL; curr = curr->next) {
        if (curr->base.on_extracted == NULL && curr->team.name == team)
            return (curr);
    }
    return (NULL);
}

void replace_egg(trantorian_t *trantorian, trantorian_t *egg)
{
    network_server_t *server = get_server(trantorian->zappy->nm, trantorian->zappy->classic_id);
    client_user_pair_t *pair = NULL;

    for (map_t curr = server->client_user_map->client_user_map; curr != NULL; curr = curr->next) {
        if (((client_user_pair_t *)curr->value)->user == &trantorian->base)
            pair = (client_user_pair_t *)curr->value;
    }
    if (pair == NULL)
        return;
    pair->user = &egg->base;
}

void response_success_connection(trantorian_t *tranto, network_client_t *nc)
{
    int slots = count_unused_slot(tranto->zappy, tranto->team.name);
    char buff[C_BUFFER_SIZE] = {0};
    size_t size = snprintf((char *)&buff, C_BUFFER_SIZE, "%i\n%i %i\n", slots\
, tranto->zappy->map_size.x, tranto->zappy->map_size.y);

    write_to_buffer(&nc->cb_out, (uint8_t *)buff, size);
}

void add_user_to_team(client_user_pair_t *pair, char *team)
{
    trantorian_t *trantorian = (trantorian_t *)pair->user;
    dim_t position = get_random_positions(trantorian->zappy->map_size);

    if (count_unused_slot(trantorian->zappy, team) > 0) {
        //TODO Egg finding and replacement
        trantorian->team.name = team;
        set_position_relative(trantorian, *trantorian->zappy->map, position);
        trantorian->next = trantorian->zappy->players;
        trantorian->zappy->players = trantorian;
    }
}