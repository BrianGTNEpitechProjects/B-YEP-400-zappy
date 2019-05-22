/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** stack_access.c
*/

/* Created the 1/4/19 at 5:39 PM by jfrabel */

#include "stack.h"

void *stack_top(stack_t stack)
{
    return (list_get_elem_at_front(stack));
}