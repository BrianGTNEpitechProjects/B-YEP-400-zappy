/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** clear_str.c
*/

/* Created the 19/06/2019 at 04:45 by jfrabel */

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

static void shift_left(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = str[i + 1];
}

static void clear_space_tab(char *str)
{
    bool was_blank = false;

    for (int i = 0; str[i]; i++) {
        if (isspace(str[i]) && was_blank) {
            shift_left(&str[i]);
            --i;
        } else if (isspace(str[i]))
            was_blank = true;
        else
            was_blank = false;
    }
}

static void replace_blank_by_space(char *str)
{
    for (int i = 0; str[i]; i++)
        if (isspace(str[i]))
            str[i] = ' ';
}

char *clear_str(char *str)
{
    int len;

    while (isspace(str[0]))
        shift_left(str);
    clear_space_tab(str);
    len = strlen(str);
    if (len != 0 && isspace(str[len - 1]))
        str[len - 1] = '\0';
    replace_blank_by_space(str);
    return (str);
}