/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:27:25 by mbarutel          #+#    #+#             */
/*   Updated: 2022/01/16 16:08:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	line_copy(char **str, char **line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(*str);
	tmp2 = *str;
	*line = ft_strdup(ft_strsep(str, "\n"));
	if (!line)
		return (-1);
	if (*str)
	{
		*str = ft_strdup(*str);
		ft_strdel(&tmp2);
	}
	if (*line[0] == '\0' && tmp[0] == '\0')
	{
		ft_strdel(line);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

static int	ret_val(int fd, int ret, char **str, char **line)
{
	if (ret < 0)
		return (-1);
	return (line_copy(&str[fd], line));
}

static int	read_ret(int fd, char *buff, char **str)
{
	int			ret;
	char		*tmp;

	if (!str[fd])
		str[fd] = ft_strdup("");
	ret = 0;
	if (!ft_strchr(str[fd], '\n'))
	{
		ret = read(fd, buff, BUFF_SIZE);
		while (ret > 0)
		{
			buff[ret] = '\0';
			tmp = ft_strjoin(str[fd], buff);
			ft_strdel(&str[fd]);
			str[fd] = tmp;
			if (ft_strchr(buff, '\n'))
				break ;
			ret = read(fd, buff, BUFF_SIZE);
		}
	}
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*str[FD_SIZE];
	char		buff[BUFF_SIZE + 1];

	if (fd >= 0 && line && fd <= FD_SIZE)
	{
		ret = read_ret(fd, buff, str);
		return (ret_val(fd, ret, str, line));
	}
	return (-1);
}
