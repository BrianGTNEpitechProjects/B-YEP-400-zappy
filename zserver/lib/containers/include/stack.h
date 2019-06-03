/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** ex03
*/

#ifndef STACK_H_
#define STACK_H_

#include "generic_list.h"

#define STACK_DEFAULT LIST_DEFAULT

typedef list_t stack_t;

/* informations */

unsigned int stack_get_size(stack_t stack);
bool stack_is_empty(stack_t stack);

/* Modification */

bool stack_push(stack_t *stack_ptr, void *elem);
bool stack_pop(stack_t *stack_ptr);

/* Access */

void *stack_top(stack_t stack);

#endif /* !STACK_H_ */
