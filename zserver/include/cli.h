/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** cli.h
*/

/* Created the 19/06/2019 at 03:25 by jfrabel */

#ifndef PSU_ZAPPY_2018_CLI_H
#define PSU_ZAPPY_2018_CLI_H

#include "zworld.h"

typedef bool (*cli_func)(zappy_t *world, char *cmd);

typedef struct cli_cmd_pair_s {
    const char *cmd_start;
    cli_func func;
} cli_cmd_pair_t;

void print_cli_welcome(void);
void print_prompt(void);

void handle_stdin(zappy_t *world);

bool cli_help(zappy_t *world, char *cmd);

#endif //PSU_ZAPPY_2018_CLI_H
