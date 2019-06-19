/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** handle_stdin.c
*/

/* Created the 19/06/2019 at 03:24 by jfrabel */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "zserver.h"

static const cli_cmd_pair_t cli_cmd_map[] = {
    {"cinfo", &cli_cinfo},
    {"drop", &cli_drop},
    {"endgame", &cli_endgame},
    {"exit", &cli_exit},
    {"help", &cli_help},
    {"kill", &cli_kill},
    {"pinfo", &cli_pinfo},
    {"timescale", &cli_timescale},
    {"tinfo", &cli_tinfo},
    {NULL, NULL}
};

static void exec_line(zappy_t *world, char *line)
{
    bool found = false;
    bool ret = false;
    const cli_cmd_pair_t *curr_cmd;

    for (int i = 0; cli_cmd_map[i].cmd_start != NULL; i++) {
        curr_cmd = &cli_cmd_map[i];
        if (!strncmp(curr_cmd->cmd_start, line, strlen(curr_cmd->cmd_start))) {
            found = true;
            ret = curr_cmd->func(world, line);
            break;
        }
    }
    if (found && !ret)
        printf("Error in parameters\n");
    if (!found)
        printf("Command not found\n");
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
    else {
        line[read - 1] = '\0';
        clear_str(line);
        exec_line(world, line);
    }
    if (running())
        print_prompt();
    free(line);
}