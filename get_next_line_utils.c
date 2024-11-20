/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:15:24 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/20 07:45:29 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*ft_lstnew(int fd)
{
	t_gnl_list	*result;

	result = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (result == NULL)
		return (NULL);
	result->fd = fd;
	result->next = NULL;
	return (result);
}

void	ft_lstadd_front(t_gnl_list **lst, t_gnl_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_check_fd(t_gnl_list *lst, int fd)
{
	while (lst)
	{
		if (lst->fd == fd)
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*array;
	unsigned int	size;
	int				i;
	int				j;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen((s1)) + ft_strlen(s2);
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			array[j++] = s1[i++];
		i = 0;
	}
	if (s2)
		while (s2[i])
			array[j++] = s2[i++];
	array[size] = '\0';
	return (array);
}

t_gnl_list	*ft_lstfind(t_gnl_list **lst, int fd)
{
	while ((*lst))
	{
		if ((*lst)->fd == fd)
			return (*lst);
		(*lst) = (*lst)->next;
	}
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (s_len < start + len)
		len = s_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
 * Step by step :
 * I need to read the file using the lst->fd or maybe just add an extra argument to ft_get_gnl_buffer().
 * Read the file while return value is not <= 0
 * If in ft_get_buffer encounter a \n i need to return everything before the \n + the \n and null terminate it '\0'
 * I need to free buffer. remove the \n + the \n and from the lst->buffer. 
*/
char		*ft_get_gnl_buffer(t_gnl_list **lst, int fd)
{
	char		*buffer;
	t_gnl_list	*actualLst;
	int			read_bytes;

	actualLst = ft_lstfind(lst, fd);
	if (!actualLst)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while(read_bytes > 0)
	{
		buffer[read_bytes] = 0;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (NULL);
}
