/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zworld.h"
#include "zitem.h"

int get_item_id_from_name(char *name, bool case_sensitive)
{
    for (int i = 0; i < TOT_ITEM_NB; ++i) {
        if (cmpstr(name, (const char *)item_map[i].name, case_sensitive) == 0)
            return (i);
    }
    return (-1);
}