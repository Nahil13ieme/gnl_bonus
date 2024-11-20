/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:03:28 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/20 07:44:04 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct gnl_list
{
	char			*buffer;
	int				fd;
	struct gnl_list	*next;
}					t_gnl_list;

t_gnl_list	*ft_lstnew(int fd);
int			ft_check_fd(t_gnl_list *list, int fd);
char		*get_next_line(int fd);
void		ft_lstadd_front(t_gnl_list **lst, t_gnl_list *new);
char		*ft_get_gnl_buffer(t_gnl_list **lst, int fd);

#endif