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
    if (pos.y - 1 < 0)
        map[pos.y][pos.x].up = &map[sz.y - 1][pos.x];
    else
        map[pos.y][pos.x].up = &map[pos.y - 1][pos.x];
    if (pos.y + 1 >= sz.y)
        map[pos.y][pos.x].down = &map[0][pos.x];
    else
        map[pos.y][pos.x].down = &map[pos.y + 1][pos.x];
    if (pos.x - 1 < 0)
        map[pos.y][pos.x].left = &map[pos.y][sz.x - 1];
    else
        map[pos.y][pos.x].left = &map[pos.y][pos.x - 1];
    if (pos.x + 1 >= sz.x)
        map[pos.y][pos.x].right = &map[pos.y][0];
    else
        map[pos.y][pos.x].right = &map[pos.y][pos.x + 1];
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