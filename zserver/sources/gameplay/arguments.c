/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** arguments.c
*/

#include <getopt.h>
#include <stdlib.h>
#include <limits.h>
#include "zserver.h"

static char **extract_teams(int index, char **av)
{
    char **teams = NULL;
    int team_count = 0;
    int curr_team = 0;

    for (int i = index; av[i] && av[i][0] != '-'; i++)
        team_count++;
    teams = calloc(team_count + 1, sizeof(*teams));
    if (teams == NULL) {
        handle_error_return("calloc: %s\n", 0);
        return (NULL);
    }
    for (int i = index; av[i] && av[i][0] != '-'; i++) {
        teams[curr_team] = av[i];
        curr_team++;
    }
    return (teams);
}

static bool extract_int(int *output, char *input)
{
    long res = strtol(input, NULL, 10);

    if (res == LONG_MIN || res == LONG_MAX) {
        return (handle_error_return("strtol: %s\n", false));
    }
    *output = (int) res;
    return (true);
}

bool parse_args(args_t *arguments, int ac, char **av)
{
    bool ret = false;

    for (int c; (c = getopt(ac, av, "p:x:y:c:f:n")) != -1; ) {
        switch (c) {
        case 'p': ret = ret || !extract_int(&arguments->port, optarg);
            break;
        case 'x': ret = ret || !extract_int(&arguments->x, optarg);
            break;
        case 'y': ret = ret || !extract_int(&arguments->y, optarg);
            break;
        case 'c': ret = ret || !extract_int(&arguments->ppt, optarg);
            break;
        case 'f': ret = ret || !extract_int(&arguments->freq, optarg);
            break;
        case 'n': arguments->teams = extract_teams(optind, av);
            ret = ret || (arguments->teams == NULL);
            break;
        default: break;
        }
    }
    return (!ret);
}
