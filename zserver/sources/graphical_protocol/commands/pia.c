/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pia.c
*/

/* Created the 18/06/2019 at 23:52 by jfrabel */

#include <string.h>
#include "graphical_protocol.h"

static int compute_player_ids_size(zappy_t *world, const char *team)
{
    char tmp[12] = {0};
    int data_size = 0;

    for (trantorian_t *curr = world->players; curr; curr = curr->next) {
        if (strcmp(curr->team.name, team) == 0)
            data_size += snprintf(tmp, 12, " %i", curr->id);
    }
    return (data_size);
}

bool pia(graphical_user_t *user, network_client_t *client,
    uint8_t *data, size_t size)
{
    zappy_t *world = user->world_infos;
    char tmp[12] = {0};
    int data_size = 0;
    char *team_name = strstr((char *)data, " ") + 1;
    int player_size = compute_player_ids_size(world, team_name);
    int team_name_size;

    data[size - 1] = '\0';
    team_name_size = strlen(team_name);
    data_size = 4 + team_name_size + player_size + 1;
    send_websocket_header(client, data_size, 1);
    write_to_buffer(&client->cb_out, (uint8_t *)"pia ", 4);
    write_to_buffer(&client->cb_out, (uint8_t *)team_name, team_name_size);
    for (trantorian_t *curr = world->players; curr; curr = curr->next) {
        if (strcmp(curr->team.name, team_name) == 0) {
            data_size = snprintf(tmp, 12, " %i", curr->id);
            write_to_buffer(&client->cb_out, (uint8_t *)tmp, data_size);
        }
    }
    write_to_buffer(&client->cb_out, (uint8_t *)"\n", 1);
    return (true);
}