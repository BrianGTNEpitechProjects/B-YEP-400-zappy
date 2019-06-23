/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** natural_spawn.c
*/

/* Created the 20/06/2019 at 17:26 by jfrabel */

#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"
#include "zserver.h"

bool cli_natural_spawn(zappy_t *world, char *cmd)
{
    char *param = strstr(cmd, " ");

    if (param == NULL) {
        printf("natural spawn of resources enabled is %s\n",
world->natural_spawn_activated ? "enabled" : "disabled");
        return (true);
    }
    if (strcmp(param + 1, "enable") == 0) {
        world->natural_spawn_activated = true;
        printf("natural spawn of resources enabled\n");
        return (true);
    }
    if (strcmp(param + 1, "disable") == 0) {
        world->natural_spawn_activated = false;
        printf("natural spawn of resources disabled\n");
        return (true);
    }
    return (false);
}