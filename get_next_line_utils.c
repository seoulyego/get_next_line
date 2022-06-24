/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:02 by yeongo            #+#    #+#             */
/*   Updated: 2022/06/08 19:27:47 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_len(char *str, size_t offset, int nl_check)
{
	size_t	length;

	if (str == NULL)
		return (0);
	length = 0;
	while (str[offset + length] && offset < BUFFER_SIZE)
	{
		length++;
		if (nl_check && str[offset + length] == '\n')
			break ;
	}
	return (length);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			m_size;
	size_t			index;

	m_size = count * size;
	tmp = malloc(m_size);
	if (tmp == NULL)
		return (NULL);
	index = 0;
	while (index < m_size)
	{
		tmp[index] = 0;
		index++;
	}
	return (tmp);
}

t_list	*ft_lstadd_back(t_list **lst)
{
	t_list	*new_node;
	t_list	*cur;

	new_node = ft_calloc(1, sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->read_size = NO_READ;
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

t_list	*remove_node(t_list **lst, t_list *node_ref)
{
	t_list	*cur;
	t_list	*tmp;

	cur = *lst;
	while (cur != NULL && cur == node_ref)
	{
		*lst = cur->next;
		free(cur);
		cur = *lst;
	}
	if (cur == NULL)
		return (NULL);
	while (cur->next != NULL)
	{
		if (cur->next == node_ref)
		{
			tmp = cur->next->next;
			free(cur->next);
			cur->next = tmp;
		}
		else
			cur = cur->next;
	}
	return (*lst);
}

ssize_t	nl_in_buffer(char *buffer, ssize_t size)
{
	ssize_t	index;

	if (buffer == NULL || size == 0)
		return (NO_NL);
	index = 0;
	while (index < size)
	{
		if (buffer[index] == '\n')
			return (index);
		index++;
	}
	return (NO_NL);
}
