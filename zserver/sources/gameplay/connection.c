/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** connection.c
*/

#include <string.h>
#include "zserver.h"

trantorian_t *get_egg_hatched(char *team, zappy_t *zap)
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

void join_team(char *name, trantorian_t *trantorian)
{
    trantorian_t *egg = NULL;

    if (count_unused_slot(trantorian->zappy, name) > 0) {
        if (count_players_team(trantorian->zappy, name) < \
trantorian->zappy->default_slots_teams)
        trantorian->team.name = name;
        else {
            egg = get_egg_hatched(name, trantorian->zappy);
            if (egg == NULL)
                return;
            replace_egg(trantorian, egg);
        }
    }
}

void response_success_connection(trantorian_t *tranto, network_client_t *nc)
{
    int slots = count_unused_slot(tranto->zappy, tranto->team.name) - 1;
    char buff[C_BUFFER_SIZE] = {0};
    size_t size = snprintf((char *)&buff, C_BUFFER_SIZE, "%i\n%i %i\n", slots\
, tranto->zappy->map_size.x, tranto->zappy->map_size.y);

    write_to_buffer(&nc->cb_out, (uint8_t *)buff, size);
}

void add_user_to_team(client_user_pair_t *pair, char *team)
{
    trantorian_t *trantorian = NULL;

    if (pair == NULL || pair->user == NULL || pair->client == NULL)
        return;
    trantorian = (trantorian_t *)pair->user;
    for (int i = 0; trantorian->zappy->teams[i].name != NULL; i++) {
        if (strcmp(trantorian->zappy->teams[i].name, team) == 0) {
            join_team(team, trantorian);
            return;
        }
    }
}