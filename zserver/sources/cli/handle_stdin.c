/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** handle_stdin.c
*/

/* Created the 19/06/2019 at 03:24 by jfrabel */

#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "zserver.h"

void print_prompt(void)
{
    printf("ZAPPY> ");
    fflush(stdout);
}

void handle_stdin(zappy_t *world)
{
    ssize_t read = 0;
    size_t len = 0;
    char *line = NULL;

    if (!running())
        return;
    read = getline(&line, &len, stdin);
    if (read <= 0)
        shutdown_server();
    printf("Got data on stdin [%s]\n", line);
    free(line);
    print_prompt();
}