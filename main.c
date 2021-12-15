/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:33:13 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/15 10:33:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int     fd;
    int     sz;
    char    *c;

    c = (char *)malloc(sizeof(char) * 100);
    if (c)
    {
        fd = open("text.txt", O_RDONLY);
        if (fd < 0)
        {
            printf("Error\n");
            return (void);
        }
        sz = read(fd, c, 10);
        printf("sz - %d : fd - %d\n");
        c[sz] = '\0';
        printf("%s\n", c);
    }
    return (void);
}