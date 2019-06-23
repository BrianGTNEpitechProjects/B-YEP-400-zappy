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

char *clear_str(char *str);

void print_cli_welcome(void);
void print_prompt(void);

void handle_stdin(zappy_t *world);

bool cli_cinfo(zappy_t *world, char *cmd);
bool cli_clear(zappy_t *world, char *cmd);
bool cli_drop(zappy_t *world, char *cmd);
bool cli_endgame(zappy_t *world, char *cmd);
bool cli_exit(zappy_t *world, char *cmd);
bool cli_help(zappy_t *world, char *cmd);
bool cli_kill(zappy_t *world, char *cmd);
bool cli_natural_spawn(zappy_t *world, char *cmd);
bool cli_nscap(zappy_t *world, char *cmd);
bool cli_pinfo(zappy_t *world, char *cmd);
bool cli_timescale(zappy_t *world, char *cmd);
bool cli_tinfo(zappy_t *world, char *cmd);

#endif //PSU_ZAPPY_2018_CLI_H
