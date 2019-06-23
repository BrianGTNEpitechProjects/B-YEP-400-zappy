/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** main.c
*/

#include <string.h>
#include <stdio.h>
#include "zserver.h"

static void display_usage(const char *progname)
{
    printf("USAGE: %s -p port -x width -y height -n name1 name2 ... nameX -c \
clientsNb [-f freq] [-w wsport] [-i]\n", progname);
    puts("\tport is the port number for the zappy server (must be > 0)");
    puts("\twidth is the width of the world (must be > 0)");
    puts("\theight is the height of the world (must be > 0)");
    puts("\tnameX is the name of the team X (at least one team)");
    puts("\tclientsNb is the number of authorized clients per team (must be >\
0)");
    puts("\tfreq is the reciprocal of time unit for execution of actions \
(must be > 0) (100 by default)");
    puts("\twsport is the port number for the ws server, \
if not set will not open the ws server (must be > 0)");
    puts("\ti option activate interactive mode and give access to a cli");
}

int main(int ac, char **av)
{
    if (ac == 1) {
        display_usage(av[0]);
        return (ERROR_EXIT);
    }
    for (int i = 0; i < ac; i++) {
        if (!strcmp(av[i], "-h") || !strcmp(av[i], "--help") ||
        !strcmp(av[i], "-help")) {
            display_usage(av[0]);
            return (SUCCESS_EXIT);
        }
    }
    if (zappy(ac, av) == false) {
        display_usage(av[0]);
        return (ERROR_EXIT);
    }
    return (SUCCESS_EXIT);
}