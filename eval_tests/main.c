/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:23:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/01/16 15:50:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../libft/includes/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

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
		printf("ret: %i line - %s\n", gnl, line);
		if (line != NULL) 
		{
			free(line);
		}
	}
	//
	// gnl = get_next_line(fd, &line);
	// printf("ret: %i line - %s\n", gnl, line);
	// if (line != NULL) 
	// {
	// 	free(line);
	// }
	// gnl = get_next_line(fd, &line);
	// printf("ret: %i line - %s\n", gnl, line);
	// if (line != NULL) 
	// {
	// 	free(line);
	// }
	// gnl = get_next_line(fd, &line);
	// printf("ret: %i line - %s\n", gnl, line);
	// if (line != NULL) 
	// {
	// 	free(line);
	// }
	//system("leaks test_gnl");
	return (0);
}
