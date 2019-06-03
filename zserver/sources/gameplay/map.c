/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** map.c
*/

#include <stdlib.h>
#include "zserver.h"

static void link_map(tile_t **map)
{

}

tile_t **create_map(int x, int y) {
    tile_t **res = calloc(1, (sizeof(tile_t *) * y) + (x * y * sizeof(tile_t)));

    if (res == NULL)
        return (NULL);
    for (int i = 0; i < y; i++)
        res[i] = (tile_t *)((uintptr_t)res + sizeof(tile_t *) * y + sizeof(tile_t) * i * x);
    link_map(res);
    return (res);
}