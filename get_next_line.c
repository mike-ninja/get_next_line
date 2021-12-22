/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:27:25 by mbarutel          #+#    #+#             */
/*   Updated: 2021/12/21 13:53:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h> // open()
#include <stdio.h> // printf()

static int  read_fd(const int fd, char **line, char *arr[FD_SIZE]);
static int  take_line(const int fd, char **line, char *ar[FD_SIZE], int end);
static int  take_last(const int fd, char **line, char *arr[FD_SIZE], int end);

int main(void)
{
    char    **line;
    int     fd;
    int     ret;
    char    *arr[FD_SIZE];
    
    ft_putendl("fd open succesful");
    fd = open("text.txt", O_RDONLY);
    ft_putstr("fd : ");
    ft_putnbr(fd);
    ft_putchar('\n');
    if (fd < 0)
        return (0);
    ret = get_next_line(fd, line);
    ft_putendl("get_next_line succesful");
    while (ret)
    {
        printf("%s\n", *line);
        line++;
        ret = get_next_line(fd, line);
    }
    return (ret);
}

int get_next_line(const int fd, char **line)
{
    static char *arr[FD_SIZE];
    
    
    if (read(fd, arr[0], 0) < 0 || !line || fd >= FD_SIZE - 1 || fd < 0 || BUFF_SIZE < 1)
        return (-1);
    printf("This happens\n");
    arr[FD_SIZE - 1] = "1";
    
    if (take_line(fd, line, arr, 1) == -1)
    {
        ft_strdel(&(arr)[fd]);
        return (-1);
    }
    if (ft_strcmp(arr[FD_SIZE - 1], "0") == 0)
    {
        *line = NULL;
        return (0);
    }
    return (1);
}

static int  read_fd(const int fd, char **line, char *arr[FD_SIZE])
{
    char    buf[BUFF_SIZE + 1];
    int     bytes_read;
    char    *tmp;

    ft_bzero(buf, BUFF_SIZE + 1);
    bytes_read = read(fd, buf, BUFF_SIZE);
    if (bytes_read > 0)
    {
        tmp = ft_strjoin(arr[fd], buf);
        if (!tmp)
            return(-1);
        ft_bzero(buf, BUFF_SIZE);
        free(arr[fd]);
        arr[fd] = tmp;
        return (take_line(fd, line, arr, 1));
    }
    else if (bytes_read < 0)
        return (0);
    return (take_line(fd, line, arr, 0));
}

static int  take_line(const int fd, char **line, char *arr[FD_SIZE], int end)
{
    int     i;
    char    *tmp;

    i = 0;
    while ((arr[fd]) && arr[fd][i])
    {
        if (arr[fd][i] == '\n')
        {
            arr[fd][i] = '\0';
            *line = ft_strdup(arr[fd]);
            if (*line)
            {
                tmp = ft_strdup(&(arr)[fd][i + 1]);
                if (tmp)
                {
                    free(arr[fd]);
                    arr[fd] = tmp;
                    return (1);
                }
                free(*line);
                return (-1);
            }
            return (-1);
        }
        i++;
    }
    return (take_last(fd, line, arr, end));
}

static int  take_last(const int fd, char **line, char *arr[FD_SIZE], int end)
{
    if (end == 0)
    {
        if (!arr[fd])
        {
            arr[FD_SIZE - 1] = "0";
            return (0);
        }
        *line = ft_strdup(arr[fd]);
        if (!*line)
            return (-1);
        if (arr[fd][0] == '\0')
            arr[FD_SIZE - 1] = "0";
        ft_bzero(arr[fd], ft_strlen(arr[fd]));
        return (0);
    }
    else
        return (read_fd(fd, line, arr));
}
