/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** cinfo.c
*/

/* Created the 19/06/2019 at 04:22 by jfrabel */

#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include "cli.h"
#include "common.h"
#include "network_server.h"

static void display_client_infos(network_client_t *client)
{
    char ip[INET_ADDRSTRLEN] = {0};
    int written = 0;
    int s_in = time(NULL) - client->last_data_in_timestamp;
    int s_out = time(NULL) - client->last_data_out_timestamp;

    inet_ntop(AF_INET, &(client->address.sin_addr), ip, INET_ADDRSTRLEN);
    written = printf("|%s:%d", ip, ntohs(client->address.sin_port));
    while (written != 22)
        written += printf(" ");
    printf("|");
    printf("%08i:%02i:%02i", s_in / 3600, (s_in % 3600) / 60, s_in % 60);
    printf("|");
    printf("%09i:%02i:%02i", s_out / 3600, (s_out % 3600) / 60, s_out % 60);
    printf("|\n");
}

static void display_server_infos(network_server_t *server)
{
    map_t curr = server->client_user_map->client_user_map;
    client_user_pair_t *pair;

    printf("Server %d opened on %hu:\n", server->id,
        ntohs(server->addr.sin_port));
    printf("----\n");
    printf("client timeout: %ld\n", server->default_client_disconnect_timeout);
    printf("world event: %ld sec %ld usec\n",
server->world_event_timeout.tv_sec, server->world_event_timeout.tv_usec);
    printf("----\nClients:\n");
    printf("|-------ip:port-------|-last-data-in-|-last-data-out-|\n");
    for (; curr; curr = curr->next) {
        pair = curr->value;
        display_client_infos(pair->client);
        if (curr->next != NULL)
            printf("|---------------------|--------------|---------------|\n");
    }
    printf("|---------------------|--------------|---------------|\n\n");
}

bool cli_cinfo(UNUSED zappy_t *world, UNUSED char *cmd)
{
    network_server_t *game_server = get_server(world->nm, world->classic_id);
    network_server_t *ws_server = get_server(world->nm, world->websocket_id);

    if (game_server)
        display_server_infos(game_server);
    if (ws_server)
        display_server_infos(ws_server);
    return (true);
}