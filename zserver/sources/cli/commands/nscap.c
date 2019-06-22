/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** nscap.c
*/

/* Created the 22/06/2019 at 11:35 by jfrabel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

static long extract_new_cap(char *cmd, bool *validator)
{
    char *nb_start = strstr(cmd, " ") + 1;
    long nb;
    char *end_ptr = NULL;

    nb = strtol(nb_start, &end_ptr, 10);
    *validator = (*end_ptr == '\0');
    return (nb);
}

bool cli_nscap(zappy_t *world, char *cmd)
{
    bool valid_cap = false;
    long new_cap = 0;
    char *args = strstr(cmd, " ");

    if (args == NULL) {
        printf("Resources spawn cap: %ld\n", world->resources_spawn_cap);
    } else {
        new_cap = extract_new_cap(cmd, &valid_cap);
        if (!valid_cap || new_cap <= 0)
            return (false);
        world->resources_spawn_cap = new_cap;
        printf("Set resources spawn cap to %ld\n", world->resources_spawn_cap);
    }
    return (true);
}