/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:47:41 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/21 06:50:56 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *s2)
{
	char *tmp;
	
	tmp = ft_strjoin(buffer, s2);
	free(buffer);
	return (tmp);
}

char	*get_buffer(char *buffer, int fd)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			free(buffer);
			return (NULL);
		}
		if(bytes_read == 0)
		{
			free(read_buffer);
			return (buffer);
		}
		buffer = ft_free(buffer, read_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(read_buffer);
	return (buffer);
}

char	*ft_remove_line(char *buffer)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	start = 0;
	i = 0;
	end = ft_strlen(buffer);
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (buffer[start] == 0)
	{
		free(buffer);
		return (NULL);
	}
	res = ft_calloc(sizeof(char), (end - start + 1));
	if (!res)
	{
		free(buffer);
		return (NULL);
	}
	while (i < (end - start) + 1)
	{
		res[i] = buffer[start + i];
		i++;
	}
	free(buffer);
	return (res);
}

char	*ft_get_line(char *buffer)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	res = calloc(sizeof(char), i + 2);
	while (buffer[j] && buffer[j] != '\n')
	{
		res[j] = buffer[j];
		j++;
	}
	if (buffer[j] == '\n')
		res[j++] = '\n';
	res[j] = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = get_buffer(buffer[fd], fd);
	if (buffer[fd] == NULL)
		return (NULL);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_remove_line(buffer[fd]);
	return (line);
}

