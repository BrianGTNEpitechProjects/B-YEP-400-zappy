/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** timescale.c
*/

/* Created the 19/06/2019 at 04:23 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"

static long extract_timescale(char *cmd, bool *validator)
{
    char *nb_start = strstr(cmd, " ") + 1;
    long nb;
    char *end_ptr = NULL;

    nb = strtol(nb_start, &end_ptr, 10);
    *validator = (*end_ptr == '\0');
    return (nb);
}

bool cli_timescale(zappy_t *world, char *cmd)
{
    bool is_valid_timescale;
    long timescale = 0;

    if (strstr(cmd, " ") != NULL) {
        timescale = extract_timescale(cmd, &is_valid_timescale);
        if (!is_valid_timescale || timescale == 0)
            return (false);
        world->time_scale = timescale;
        printf("New timescale set to %i\n", world->time_scale);
    } else {
        printf("Current timescale is set to %i\n", world->time_scale);
    }
    return (true);
}