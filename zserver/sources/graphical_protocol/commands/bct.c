/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** btc.c
*/

/* Created the 17/06/2019 at 20:05 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include "graphical_protocol.h"

static void send_tile_data(network_client_t *client, tile_t *tile, int x, int y)
{
    char to_send[113] = {0};
    int food = tile->content[0];
    int linemate = tile->content[1];
    int deraumere = tile->content[2];
    int sibur = tile->content[3];
    int mendiane = tile->content[4];
    int phiras = tile->content[5];
    int thystame = tile->content[6];
    int size;

    size = snprintf(to_send, 112, "bct %i %i %i %i %i %i %i %i %i\n", x, y,
        food, linemate, deraumere, sibur, mendiane, phiras, thystame);
    send_websocket(client, (uint8_t *)to_send, size, 1);
}

static bool extract_tiles_and_awnser(graphical_user_t *user,
    network_client_t *client, char *extracted)
{
    char *first_nb = strstr(extracted, " ") + 1;
    char *second_nb = strstr(first_nb, " ") + 1;
    int x = strtol(first_nb, NULL, 10);
    int y = strtol(second_nb, NULL, 10);
    tile_t *requested_tile;

    if (x < 0 || y < 0 || x >= user->world_infos->map_size.x ||
    y >= user->world_infos->map_size.y)
        return (false);
    requested_tile = &(user->world_infos->map[y][x]);
    send_tile_data(client, requested_tile, x, y);
    return (true);
}

bool bct(graphical_user_t *user, network_client_t *client,
    uint8_t *data, size_t size)
{
    regex_t preg = {0};
    regmatch_t regmatch[10] = {0};
    char extracted[C_BUFFER_SIZE] = {0};

    memcpy(extracted, data, size);
    if (regcomp(&preg, "^bct [0-9]{1,11} [0-9]{1,11}\n", REG_EXTENDED))
        return (false);
    if (regexec(&preg, extracted, 10, regmatch, 0)) {
        regfree(&preg);
        return (false);
    }
    regfree(&preg);
    return (extract_tiles_and_awnser(user, client, extracted));
}