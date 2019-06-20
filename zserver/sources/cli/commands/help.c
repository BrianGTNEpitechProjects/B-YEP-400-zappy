/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** help.c
*/

/* Created the 19/06/2019 at 03:46 by jfrabel */

#include <stdio.h>
#include "cli.h"
#include "common.h"

static void display_ressources_ids(void)
{
    puts("\nResources ids:");
    puts("0 => food");
    puts("1 => linemate");
    puts("2 => deraumere");
    puts("3 => sibur");
    puts("4 => mendiane");
    puts("5 => phiras");
    puts("6 => thystame");
}

bool cli_help(UNUSED zappy_t *world, UNUSED char *cmd)
{
    puts("Zappy interactive command line help:");
    puts("help           : display this help");
    puts("cinfo          : display information about all connected clients");
    puts("clear          : clear all resources on the map \
(can take time and induce lags on big worlds)");
    puts("pinfo id       : display information about the player with the id \
id, if id is not set will display info about all players");
    puts("tinfo x y      : display information about the tile at pos x y");
    puts("timescale t    : set the timescale value to t, if not set will \
display the current timescale instead");
    puts("drop r x y     : drop the resource id r at position x y");
    puts("naturalspawn b : enable/disable/display natural ressource spawning \
(b must be enable or disable or empty)");
    puts("kill id        : kill the player with the id id");
    puts("[WIP]endgame   : end the current running game and exit");
    puts("exit           : exit the program");
    display_ressources_ids();
    return (true);
}