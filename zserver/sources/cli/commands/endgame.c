/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** endgame.c
*/

/* Created the 19/06/2019 at 04:24 by jfrabel */

#include <stdio.h>
#include "cli.h"
#include "common.h"

bool cli_endgame(zappy_t *world, UNUSED char *cmd)
{
    end_game(world, NULL);
    return (true);
}