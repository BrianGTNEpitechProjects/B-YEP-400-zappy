/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** connection.c
*/

#include <string.h>
#include "zserver.h"
#include "zworld.h"
#include "graphical_protocol.h"

trantorian_t *get_egg_hatched(const char *team, zappy_t *zap)
{
    for (trantorian_t *curr = zap->players; curr != NULL; curr = curr->next) {
        if (curr->base.on_extracted == &on_extract_connected && curr->is_egg \
&& !strcmp(team, curr->team->name))
            return (curr);
    }
    return (NULL);
}

void replace_egg(trantorian_t *trantorian, trantorian_t *egg)
{
    network_server_t *server = get_server(trantorian->zappy->nm, \
trantorian->zappy->classic_id);
    client_user_pair_t *pair = NULL;

    for (map_t c = server->client_user_map->client_user_map; c != NULL; \
c = c->next) {
        if (((client_user_pair_t *)c->value)->user == &trantorian->base)
            pair = (client_user_pair_t *)c->value;
    }
    if (pair == NULL)
        return;
    pair->user = &egg->base;
}

void response_success_connection(trantorian_t *tranto, network_client_t *nc)
{
    int slots = count_unused_slot(tranto->zappy, tranto->team->name);
    char buff[C_BUFFER_SIZE] = {0};
    size_t size = snprintf((char *)&buff, C_BUFFER_SIZE, "%i\n%i %i\n", slots\
, tranto->zappy->map_size.x, tranto->zappy->map_size.y);

    write_to_buffer(&nc->cb_out, (uint8_t *)buff, size);
}

trantorian_t * add_user_to_team(client_user_pair_t *pair, team_t *team)
{
    trantorian_t *trantorian = (trantorian_t *)pair->user;
    trantorian_t *egg = NULL;
    dim_t pos = get_random_positions(trantorian->zappy->map_size);

    if (count_unused_slot(trantorian->zappy, team->name) > 0) {
        egg = get_egg_hatched(team->name, trantorian->zappy);
        if (egg == NULL) {
            trantorian->team = team;
            set_position_relative(trantorian, *trantorian->zappy->map, pos);
            trantorian->next = trantorian->zappy->players;
            trantorian->zappy->players = trantorian;
            pnw(trantorian->zappy, trantorian);
        } else {
            replace_egg(trantorian, egg);
            ebo(trantorian->zappy, egg);
            return (egg);
        }
    }
    return (trantorian);
}