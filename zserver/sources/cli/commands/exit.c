/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** exit.c
*/

/* Created the 19/06/2019 at 04:24 by jfrabel */

#include <stdio.h>
#include "cli.h"
#include "common.h"
#include "zserver.h"

bool cli_exit(UNUSED zappy_t *world, UNUSED char *cmd)
{
    shutdown_server();
    return (true);
}