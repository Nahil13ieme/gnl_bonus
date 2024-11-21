/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:47:41 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/21 01:58:55 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer(char *buffer, int fd)
{
	char	*readBuffer;
	size_t	bytesRead;
	
	readBuffer = ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
	if(!readBuffer)
		return (NULL);
	bytesRead = 1;
	while(bytesRead > 0)
	{
		bytesRead = read(fd, readBuffer, BUFFER_SIZE);
		if(bytesRead == -1)
		{
			free(readBuffer);
			free(buffer);
			return (NULL);
		}
		buffer = ft_strjoin(buffer, readBuffer);
		if(ft_strchr(buffer, '\n'));
			break;
	}
	free(readBuffer);
	return(buffer);
}

char	*ft_get_line(char *buffer)
{
	char	*res;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while(buffer[i] && buffer[i] != '\n')
		i++;
	res = calloc(sizeof(char *), i);
	while(i >= 0)
	{
		res[j] = buffer[j];
		j++;
	}	
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	
	buffer[fd] = get_buffer(buffer, fd);
	
	
	return(line);
}
