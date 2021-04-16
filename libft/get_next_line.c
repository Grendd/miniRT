/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrigil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:30:17 by qrigil            #+#    #+#             */
/*   Updated: 2020/11/27 19:30:19 by qrigil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

static void		ft_strclr(char *s)
{
	if (s)
		while (*s)
			*s++ = '\0';
}

static char		*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char		*remainder_check(char **line, char *remainder)
{
	char	*p_newline;

	p_newline = NULL;
	if (remainder)
	{
		if ((p_newline = ft_strchr(remainder, '\n')))
		{
			*p_newline = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, ++p_newline);
		}
		else
		{
			*line = ft_strdup(remainder);
			ft_strclr(remainder);
		}
	}
	else
		*line = ft_strnew(1);
	return (p_newline);
}

static int		free_mem(char **str, int res, char **p_n)
{
	char *leak;

	if (p_n != NULL)
	{
		leak = *str;
		*str = ft_strdup(++*p_n);
		free(leak);
	}
	else if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (res);
}

int				get_next_line(int fd, char **line)
{
	static char		*remainder;
	char			*p_newline;
	char			*leak;
	char			*buf;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line ||
		!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))) ||
		read(fd, buf, 0) || (!remainder && !(remainder = ft_strdup(""))))
		return (-1);
	p_newline = remainder_check(line, remainder);
	while (!p_newline && (bytes_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_read] = '\0';
		if ((p_newline = ft_strchr(buf, '\n')) != NULL)
		{
			*p_newline = '\0';
			free_mem(&remainder, 0, &p_newline);
		}
		leak = *line;
		*line = ft_strjoin(*line, buf);
		free(leak);
	}
	free(buf);
	return (!bytes_read && !*remainder) ? free_mem(&remainder, 0, NULL) : 1;
}
