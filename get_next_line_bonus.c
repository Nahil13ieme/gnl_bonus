/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:47:41 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/21 22:54:26 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, s2);
	if (!tmp)
		return (NULL);
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
		if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = '\0';
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
	int		i;
	char	*res;

	start = 0;
	i = 0;
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (buffer[start] == 0)
		return (free(buffer), NULL);
	res = ft_calloc(sizeof(char), (ft_strlen(buffer) - start++));
	if (!res)
		return (free(buffer), NULL);
	while (buffer[start + i])
	{
		res[i] = buffer[start + i];
		i++;
	}
	return (free(buffer), res);
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
	if (!res)
		return (NULL);
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
	if (buffer[fd] == NULL || buffer[fd][0] == 0)
		return (NULL);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_remove_line(buffer[fd]);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("variable_nls.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }