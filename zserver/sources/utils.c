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

int handle_error_return(char *s, int ret)
{
    fprintf(stderr, s, strerror(errno));
    return (ret);
}

char *concat(char *str1, char *str2, bool free1, bool free2)
{
    char *res = NULL;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (str1 == NULL || str2 == NULL)
        return (NULL);
    res = malloc((size_t)(len1 + len2 + 1));
    if (res == NULL)
        return (NULL);
    for (size_t i = 0; i < len1; i++)
        res[i] = str1[i];
    for (size_t i = 0; i < len2; i++)
        res[len1 + i] = str2[i];
    res[len1 + len2] = '\0';
    if (free1)
        free(str1);
    if (free2)
        free(str2);
    return (res);
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