/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:02 by yeongo            #+#    #+#             */
/*   Updated: 2022/07/21 20:17:51 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_len(char *str, size_t offset)
{
	size_t	length;

	if (str == NULL)
		return (0);
	length = 0;
	while (str[offset + length] && str[offset + length] != '\n')
		length++;
	if (str[offset + length] == '\n')
		return (length + 1);
	return (length);
}

t_list	*ft_lstadd_back(t_list **lst, int fd)
{
	t_list	*new_node;
	t_list	*cur;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->read_fd = fd;
	new_node->read_size = NO_READ;
	new_node->offset = 0;
	new_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_node;
		return (new_node);
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_node;
	return (new_node);
}

t_list	*remove_node(t_list **lst, t_list **node_ref)
{
	t_list	*cur;
	t_list	*tmp;

	cur = *lst;
	if (cur != NULL && cur == *node_ref)
	{
		*lst = cur->next;
		free(cur);
		cur = *lst;
		*node_ref = NULL;
	}
	while (cur != NULL && cur->next != NULL)
	{
		if (cur->next == *node_ref)
		{
			tmp = cur->next->next;
			free(cur->next);
			cur->next = tmp;
			*node_ref = NULL;
			break ;
		}
		else
			cur = cur->next;
	}
	return (*lst);
}

ssize_t	nl_in_buffer(char *buffer)
{
	ssize_t	index;

	if (buffer == NULL)
		return (NO_NL);
	index = 0;
	while (buffer[index])
	{
		if (buffer[index] == '\n')
			return (index);
		index++;
	}
	return (NO_NL);
}
