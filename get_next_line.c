/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:47:41 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/20 07:48:39 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*stash;

	if (!stash)
		stash = ft_lstnew(fd);
	if (!ft_check_fd(stash, fd))
		ft_lstadd_front(&stash, ft_lstnew(fd));
	return (ft_get_gnl_buffer(&stash, fd));
}
