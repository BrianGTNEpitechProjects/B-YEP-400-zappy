/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** clear.c
*/

/* Created the 20/06/2019 at 17:34 by jfrabel */

#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"
#include "zserver.h"

bool cli_clear(zappy_t *world, UNUSED char *cmd)
{
    printf("clearing map (can take time on big maps)...\n");
    for (int y = 0; y < world->map_size.y; ++y) {
        for (int x = 0; x < world->map_size.x; ++x) {
            world->map[y][x].content[0] = 0;
            world->map[y][x].content[1] = 0;
            world->map[y][x].content[2] = 0;
            world->map[y][x].content[3] = 0;
            world->map[y][x].content[4] = 0;
            world->map[y][x].content[5] = 0;
            world->map[y][x].content[6] = 0;
        }
    }
    printf("map cleared\n");
    return (true);
}