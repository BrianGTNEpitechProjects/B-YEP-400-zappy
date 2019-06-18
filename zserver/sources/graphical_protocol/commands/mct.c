/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** mct.c
*/

/* Created the 17/06/2019 at 20:05 by jfrabel */

#include "graphical_protocol.h"

static void write_map_tile(network_client_t *client, tile_t *tile, int x, int y)
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
    write_to_buffer(&client->cb_out, (uint8_t *)to_send, size);
}

static int compute_tile_length(tile_t *tile, int x, int y)
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
    return (size);
}

static int compute_map_length(zappy_t *world)
{
    int tot_size = 0;

    for (int y = 0; y < world->map_size.y; ++y) {
        for (int x = 0; x < world->map_size.x; ++x) {
            tot_size += compute_tile_length(&world->map[y][x], x, y);
        }
    }
    return (tot_size);
}

//FIXME modify so that the ws max payload size doesn't break everything
bool mct(graphical_user_t *user, network_client_t *client,
    UNUSED uint8_t *data, UNUSED size_t size)
{
    int data_len = compute_map_length(user->world_infos);
    uint8_t to_write = 0b10000000 + 1;

    write_to_buffer(&client->cb_out, &to_write, 1);
    to_write = data_len & 0b011111111;
    write_to_buffer(&client->cb_out, &to_write, 1);
    for (int y = 0; y < user->world_infos->map_size.y; ++y) {
        for (int x = 0; x < user->world_infos->map_size.x; ++x) {
            write_map_tile(client, &user->world_infos->map[y][x], x, y);
        }
    }
    return (true);
}