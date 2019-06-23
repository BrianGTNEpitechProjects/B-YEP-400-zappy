/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** base64.c
*/

/* Created the 29/05/2019 at 10:11 by brian */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "zserver.h"

static int get_output_from_triple(char *res, unsigned int triple, int osize, \
size_t length)
{
    const char *base64 = \
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t to_move = 18;
    size_t modified = 0;

    for (int i = 0; i < 4 && osize > 0; i++) {
        res[i] = base64[(triple >> to_move) & 0b111111];
        to_move -= 6;
        modified++;
        length--;
        osize--;
    }
    return (modified);
}

unsigned int get_base64_size(size_t length)
{
    return ((length / 3) * 4) + (((length % 3) > 0) * 4);
}

char *base64_encode(unsigned char *str, size_t length)
{
    const char mods[] = {0, 2, 1};
    size_t output_size = get_base64_size(length);
    char *res = calloc(output_size, sizeof(*res));
    unsigned int triple = 0;
    size_t j = 0;

    if (res == NULL)
        return (NULL);
    for (size_t i = 0; i < length;) {
        triple = str[i++];
        triple = (triple << 8);
        if (i < length)
            triple += str[i++];
        triple = triple << 8;
        if (i < length)
            triple += str[i++];
        j += get_output_from_triple(&res[j], triple, output_size - j, length);
    }
    for (int i = 0; i < mods[length % 3]; i++)
        res[output_size - 1 - i] = '=';
    return (res);
}