/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:33:41 by bkandemi          #+#    #+#             */
/*   Updated: 2022/01/05 15:51:06 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		gnl;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (ft_strequ(line, "1234567 1234567") != 1)
		{
			printf("mid: [ko]\n");
			printf("line: %s\n", line);
			return (1);
		}
		if (line != NULL)
			free(line);
	}
	printf("mid: [ok]\n");
	//system("leaks test_gnl");
	return (0);
}