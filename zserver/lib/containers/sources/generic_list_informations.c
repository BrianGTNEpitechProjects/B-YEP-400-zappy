/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** informations.c
*/

/* Created the 1/4/19 at 5:09 PM by jfrabel */

#include <stddef.h>
#include "generic_list.h"

unsigned int list_get_size(list_t list)
{
    unsigned int nb = 0;

    while (list != NULL) {
        nb++;
        list = list->next;
    }
    return (nb);
}

bool list_is_empty(list_t list)
{
    return (list == NULL);
}

void list_dump(list_t list, value_displayer_t val_disp)
{
    while (list != NULL) {
        (*val_disp)(list->value);
        list = list->next;
    }
}