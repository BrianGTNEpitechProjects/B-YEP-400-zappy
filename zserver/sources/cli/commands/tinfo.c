/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** tinfo.c
*/

/* Created the 19/06/2019 at 04:23 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"

static bool extract_positions(char *cmd, int *x, int *y)
{
    char *x_start = strstr(cmd, " ");
    char *y_start;
    char *end_ptr = NULL;

    if (x_start == NULL)
        return (false);
    y_start = strstr(x_start + 1, " ");
    if (y_start == NULL)
        return (false);
    *x = strtol(x_start + 1, &end_ptr, 10);
    if (end_ptr != y_start)
        return (false);
    *y = strtol(y_start + 1, &end_ptr, 10);
    if (*end_ptr != '\0')
        return (false);
    return (true);
}

static void display_tile(tile_t *tile)
{
    char *item_str[] = {"food", "linemate", "deraumere", "sibur",
"mendiane", "phiras", "thystame"};
    trantorian_t *curr = tile->first;

    printf("Tile %i %i:\n", tile->coords.x, tile->coords.y);
    printf("Content:\n");
    for (int i = 0; i < 7; i++)
        printf("-[%i](%s) => %i\n", i, item_str[i], tile->content[i]);
    printf("Trantorian and eggs ids:\n");
    if (curr == NULL)
        printf("-Empty\n");
    else {
        printf("-%i\n", curr->id);
        curr = curr->neighbour;
        for (; curr != tile->first; curr = curr->neighbour) {
            printf("-%i\n", curr->id);
        }
    }
}

bool cli_tinfo(zappy_t *world, char *cmd)
{
    int x;
    int y;

    if (!extract_positions(cmd, &x, &y))
        return (false);
    if (x < 0 || y < 0 || x >= world->map_size.x || y >= world->map_size.y)
        return (false);
    display_tile(&world->map[y][x]);
    return (true);
}