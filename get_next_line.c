/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:27:25 by mbarutel          #+#    #+#             */
/*   Updated: 2022/01/05 14:20:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	line_copy(char **str, char **line);
static int	read_ret(int fd, char *buff, char **str);
static int	ret_val(int fd, int ret, char **str, char **line);

int	get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*str[FD_SIZE];
	char		buff[BUFF_SIZE + 1];

	if (fd >= 0 && line)
	{
		ret = read_ret(fd, buff, str);
		return (ret_val(fd, ret, str, line));
	}
	return (-1);
}

static int	read_ret(int fd, char *buff, char **str)
{
	int			ret;
	char		*tmp;

	ret = read(fd, buff, BUFF_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str[fd], buff);
			ft_strdel(&str[fd]);
			str[fd] = tmp;
		}
		if (strchr(str[fd], '\n'))
			break ;
		ret = read(fd, buff, BUFF_SIZE);
	}
	return (ret);
}

static int	ret_val(int fd, int ret, char **str, char **line)
{
	if (ret < 0)
		return (-1);
	if (ret == 0 && !str[fd])
		return (0);
	return (line_copy(&str[fd], line));
}

static int	line_copy(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_strsub((*str), 0, i);
		tmp = ft_strdup(&(*str)[i + 1]);
		ft_strdel(str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}
