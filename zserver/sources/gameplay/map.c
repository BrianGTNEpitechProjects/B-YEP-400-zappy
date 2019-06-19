/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** map.c
*/

#include <stdlib.h>
#include "zserver.h"

static void link_neighbours(tile_t **map, pos_t pos, pos_t sz)
{
    map[pos.y][pos.x].coords = pos;
    if (pos.y - 1 < 0)
        map[pos.y][pos.x].north = &map[sz.y - 1][pos.x];
    else
        map[pos.y][pos.x].north = &map[pos.y - 1][pos.x];
    if (pos.y + 1 >= sz.y)
        map[pos.y][pos.x].south = &map[0][pos.x];
    else
        map[pos.y][pos.x].south = &map[pos.y + 1][pos.x];
    if (pos.x - 1 < 0)
        map[pos.y][pos.x].west = &map[pos.y][sz.x - 1];
    else
        map[pos.y][pos.x].west = &map[pos.y][pos.x - 1];
    if (pos.x + 1 >= sz.x)
        map[pos.y][pos.x].east = &map[pos.y][0];
    else
        map[pos.y][pos.x].east = &map[pos.y][pos.x + 1];
}

static void link_map(tile_t **map, dim_t size)
{
    for (int i = 0; i < size.y; i++)
        for (int j = 0; j < size.x; j++) {
            link_neighbours(map, (pos_t){.x = j, .y = i}, size);
        }
}

tile_t **create_map(int x, int y) {
    tile_t **res = calloc(1, (sizeof(tile_t *) * y) + (x * y * sizeof(tile_t)));
    if (res == NULL)
        return (NULL);
    for (int i = 0; i < y; i++)
        res[i] = (tile_t *)((uintptr_t)res + sizeof(tile_t *) * y + sizeof(tile_t) * i * x);
    link_map(res, (dim_t){.x = x, .y = y});
    return (res);
}

pos_t get_random_positions(dim_t map_size)
{
    pos_t res;

    res.x = rand() % map_size.x;
    res.y = rand() % map_size.y;
    return (res);
}

void set_position(trantorian_t *to_place, tile_t *tile)
{
    trantorian_t *relink = NULL;

    if (to_place->pos) {
        for (relink = to_place->pos->first; relink->neighbour != to_place; \
relink = relink->neighbour);
        relink->neighbour = to_place->neighbour;
    }
    to_place->pos = tile;
    if (tile->first == NULL) {
        tile->first = to_place;
        to_place->neighbour = to_place;
    } else {
        to_place->neighbour = tile->first;
        for (relink = tile->first; relink->neighbour != tile->first; \
relink = relink->neighbour);
        relink->neighbour = to_place;
    }
}
