/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** drop.c
*/

/* Created the 19/06/2019 at 04:23 by jfrabel */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"
#include "zserver.h"

static bool extract_positions(char *cmd, int *r, int *x, int *y)
{
    char *r_start = strstr(cmd, " ");
    char *x_start = r_start ? strstr(r_start + 1, " ") : NULL;
    char *y_start = x_start ? strstr(x_start + 1, " ") : NULL;
    char *end_ptr = NULL;

    if (r_start == NULL || x_start == NULL || y_start == NULL)
        return (false);
    *r = strtol(r_start + 1, &end_ptr, 10);
    if (end_ptr != x_start)
        return (false);
    *x = strtol(x_start + 1, &end_ptr, 10);
    if (end_ptr != y_start)
        return (false);
    *y = strtol(y_start + 1, &end_ptr, 10);
    if (*end_ptr != '\0')
        return (false);
    return (true);
}

bool cli_drop(UNUSED zappy_t *world, char *cmd)
{
    int r;
    int x;
    int y;

    if (!extract_positions(cmd, &r, &x, &y))
        return (false);
    if (r < 0 || r >= TOT_ITEM_NB)
        return (false);
    if (x < 0 || y < 0 || x >= world->map_size.x || y >= world->map_size.y)
        return (false);
    spawn_resource(&world->map[y][x], r);
    printf("Dropped item of type %i at %i %i\n", r, x, y);
    return (true);
}