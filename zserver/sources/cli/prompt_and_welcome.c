/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** prompt_and_welcome.c
*/

/* Created the 19/06/2019 at 03:43 by jfrabel */

#include <stdio.h>
#include <stdlib.h>
#include "cli.h"

void print_prompt(void)
{
    printf("ZAPPY> ");
    fflush(stdout);
}

void print_cli_welcome(void)
{
    printf("Welcome to the zappy interactive mode. For help type help.\n");
    print_prompt();
}