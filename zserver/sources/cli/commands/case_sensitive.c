/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** casesensitive.c
*/

#include <stdio.h>
#include <string.h>
#include "zworld.h"
#include "cli.h"
#include "common.h"

bool cli_case_sensitive(zappy_t *world, char *cmd)
{
    char *param = strstr(cmd, " ");

    if (param == NULL) {
        printf("Case sensitive mode is %s\n",
world->case_sensitive_inputs ? "enabled" : "disabled");
        return (true);
    }
    if (strcmp(param + 1, "true") == 0 || strcmp(param + 1, "1") == 0) {
        world->case_sensitive_inputs = true;
        printf("Case sensitive mode is enabled\n");
        return (true);
    }
    if (strcmp(param + 1, "false") == 0 || strcmp(param + 1, "0") == 0) {
        world->case_sensitive_inputs = false;
        printf("Case sensitive mode is disabled\n");
        return (true);
    }
    return (false);
}

int cmpstr(const char *s1, const char *s2, bool case_sensitive)
{
    if (case_sensitive)
        return (strcmp(s1, s2));
    else
        return (strcasecmp(s1, s2));
}

int cmpnstr(const char *s1, const char *s2, bool case_sensitive, int n)
{
    if (case_sensitive)
        return (strncmp(s1, s2, n));
    else
        return (strncasecmp(s1, s2, n));
}