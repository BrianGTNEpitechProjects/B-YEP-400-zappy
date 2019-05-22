/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** stack_informations.c
*/

/* Created the 1/4/19 at 5:35 PM by jfrabel */

#include "stack.h"

unsigned int stack_get_size(stack_t stack)
{
    return (list_get_size(stack));
}

bool stack_is_empty(stack_t stack)
{
    return (list_is_empty(stack));
}