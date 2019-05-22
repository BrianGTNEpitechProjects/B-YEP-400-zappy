/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** stack_modifications.c
*/

/* Created the 1/4/19 at 5:37 PM by jfrabel */

#include "stack.h"

bool stack_push(stack_t *stack_ptr, void *elem)
{
    return (list_add_elem_at_front(stack_ptr, elem));
}

bool stack_pop(stack_t *stack_ptr)
{
    return (list_del_elem_at_front(stack_ptr));
}