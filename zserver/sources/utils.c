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
