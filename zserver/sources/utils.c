/*
** EPITECH PROJECT, 2018
** utils.c
** File description:
** Common useful functions
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include "zposition.h"
#include "zworld.h"

int handle_error_return(char *s, int ret)
{
    fprintf(stderr, s, strerror(errno));
    return (ret);
}

bool check_data_encoding(const uint8_t *data, size_t data_len)
{
    for (size_t i = 0; i < data_len; ++i) {
        if (data[i] > 127)
            return (false);
    }
    return (true);
}

int cardinal_to_int(e_cardinal_t cardinal)
{
    switch (cardinal) {
    case NORTH:
        return (1);
    case EAST:
        return (2);
    case SOUTH:
        return (3);
    case WEST:
        return (4);
    default:
        return (0);
    }
}

int item_to_int(e_item_t item)
{
    switch (item) {
    case FOOD:
        return (0);
    case LINEMATE:
        return (1);
    case DERAUMERE:
        return (2);
    case SIBUR:
        return (3);
    case MENDIANE:
        return (4);
    case PHIRAS:
        return (5);
    case THYSTAME:
        return (6);
    default:
        return (-1);
    }
}