/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** connection.c
*/

#include <string.h>
#include "zserver.h"

void join_team(char *name, trantorian_t *trantorian) {

    trantorian->team.name = name;
}

void response_success_connection(trantorian_t *tranto, network_client_t *nc) {
    int slots = tranto->zappy->default_slots_teams;
    char buff[C_BUFFER_SIZE] = {0};
    size_t size = 0;

    for (trantorian_t *pl = tranto->zappy->players; pl != NULL; pl = pl->next) {
        if (strcmp(pl->team.name, tranto->team.name) == 0)
            slots += (pl->base.on_disconnect == NULL) ? 1 : -1;
    }
    size = snprintf((char *) &buff, C_BUFFER_SIZE, "%i\n%i %i\n", slots, \
tranto->zappy->map_size.x, tranto->zappy->map_size.y);
    write_to_buffer(&nc->cb_out, (uint8_t *)buff, size);
}

void add_user_to_team(client_user_pair_t *pair, uint8_t *data, size_t sz) {
    trantorian_t *trantorian = NULL;
    char *team_name = (char *)data;

    if (pair == NULL || pair->user == NULL || pair->client == NULL)
        return;
    trantorian = (trantorian_t *)pair->user;
    for (int i = 0; trantorian->zappy->teams[i].name != NULL; i++) {
        if (strncmp(trantorian->zappy->teams[i].name, team_name, sz - 1) == 0) {
            join_team(team_name, trantorian);
            return;
        }
    }
}