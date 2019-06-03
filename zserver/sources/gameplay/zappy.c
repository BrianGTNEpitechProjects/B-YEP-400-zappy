/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy.c
*/

#include "zserver.h"

bool zappy(int ac, char **av)
{
    args_t arguments = {0};

    if (parse_args(&arguments, ac, av) == false)
        return (false);
    return (true);
}