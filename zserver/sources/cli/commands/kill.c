/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** kill.c
*/

/* Created the 19/06/2019 at 04:23 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"
#include "graphical_protocol.h"

static long extract_id(char *cmd, bool *validator)
{
    char *nb_start = strstr(cmd, " ") + 1;
    long nb;
    char *end_ptr = NULL;

    nb = strtol(nb_start, &end_ptr, 10);
    *validator = (*end_ptr == '\0');
    return (nb);
}

bool cli_kill(UNUSED zappy_t *world, char *cmd)
{
    bool is_valid_id;
    long id = 0;
    trantorian_t *player;

    if (strstr(cmd, " ") != NULL) {
        id = extract_id(cmd, &is_valid_id);
        player = find_trantorian_by_id(world, id);
        if (!is_valid_id || player == NULL)
            return (false);
        //todo kill player
        printf("[WIP] we should kill player id %i\n", id);
    } else
        return (false);
    return (true);
}