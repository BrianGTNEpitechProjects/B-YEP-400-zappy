/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zworld.h"

int get_item_id_from_name(char *name)
{
    for (int i = 0; i < TOT_ITEM_NB; ++i) {
        if (strcmp(name, (const char *)item_map[i].name) == 0)
            return (i);
    }
    return (-1);
}