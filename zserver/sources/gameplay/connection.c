/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** connection.c
*/

#include <string.h>
#include "zserver.h"

int count_unused_slot(zappy_t *zap, char *team_name)
{
    int tot = 0;
    int if_no_eggs = zap->default_slots_teams;

    for (trantorian_t *node = zap->players; node; node = node->next) {
        if (team_name == NULL || strcmp(node->team.name, team_name) == 0) {
            tot += (node->base.on_disconnect == NULL);
            if_no_eggs -= (node->base.on_disconnect == NULL);
        }
    }
    return (tot < zap->default_slots_teams ? if_no_eggs : tot);
}

void join_team(char *name, trantorian_t *trantorian)
{
    if (count_unused_slot(trantorian->zappy, name) > 0) {
        trantorian->team.name = name;
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