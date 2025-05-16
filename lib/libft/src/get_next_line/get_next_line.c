/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:49:08 by aranger           #+#    #+#             */
/*   Updated: 2024/02/06 18:55:44 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*set_line(char *line)
{
	char	*cutline;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	if (line[i] == '\0')
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == '\0')
			return (line);
		i++;
	}
	cutline = ft_calloc(i + 2, sizeof(char));
	if (cutline == NULL)
		return (NULL);
	i = 0;
	while (line [i] != '\n' && line[i] != '\0')
	{
		cutline[i] = line[i];
		i++;
	}
	cutline[i] = line[i];
	return (cutline);
}

static char	*read_buffer(int fd, char *rest)
{
	char	*line;
	char	*tmp;
	int		readsize;

	readsize = 1;
	if (rest)
		line = rest;
	else
		line = ft_calloc((1), sizeof(char));
	while (line)
	{
		tmp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (tmp == NULL)
			return (NULL);
		readsize = read(fd, tmp, BUFFER_SIZE);
		if (readsize <= 0)
		{
			free(tmp);
			break ;
		}
		line = ft_strjoin_gnl(line, tmp);
		if (ft_strrchr(line, '\n') != NULL)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*tmp;
	char		*line;

	if (fd < 0)
		return (NULL);
	tmp = read_buffer(fd, rest);
	line = set_line(tmp);
	if (tmp)
		free(tmp);
	if (!line && !rest)
		return (NULL);
	return (line);
}
