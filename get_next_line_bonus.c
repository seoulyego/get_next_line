/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:09:54 by yeongo            #+#    #+#             */
/*   Updated: 2022/07/21 20:53:23 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	read_fd(t_list **lst, t_list **cur, int fd)
{
	*cur = ft_lstadd_back(lst, fd);
	if (*cur == NULL)
		return (ERROR);
	(*cur)->read_size = read(fd, (*cur)->buffer, BUFFER_SIZE);
	if ((*cur)->read_size == -1)
		return (ERROR);
	else if ((*cur)->read_size == 0)
		return (READ_EOF);
	(*cur)->buffer[(*cur)->read_size] = '\0';
	return (SUCCESS);
}

int	get_line(char **dst, t_list *node)
{
	char	*result;
	ssize_t	m_size;
	ssize_t	index;

	m_size = line_len(*dst, 0) + line_len(node->buffer, node->offset);
	result = malloc(sizeof(char) * (m_size + 1));
	if (result == NULL)
		return (ERROR);
	index = 0;
	while (*dst != NULL && (*dst)[index] != '\0')
	{
		result[index] = (*dst)[index];
		index++;
	}
	while (index < m_size && node->offset < node->read_size)
	{
		result[index] = node->buffer[node->offset];
		node->offset++;
		index++;
	}
	result[index] = '\0';
	if (*dst != NULL)
		free(*dst);
	*dst = result;
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*cur;
	char			*read_line;
	int				result;

	cur = lst;
	read_line = NULL;
	while (cur != NULL && cur->read_fd != fd)
		cur = cur->next;
	if (read(fd, NULL, 0) == -1)
		return (fail_to_read_fd(ERROR, read_line, &lst, &cur));
	while (nl_in_buffer(read_line) == NO_NL)
	{
		if (cur == NULL)
		{
			result = read_fd(&lst, &cur, fd);
			if (result != SUCCESS)
				return (fail_to_read_fd(result, read_line, &lst, &cur));
		}
		if (cur->offset < cur->read_size)
		{
			result = get_line(&read_line, cur);
			if (result != SUCCESS)
				return (fail_to_get_line(&lst, &read_line));
		}
		if (cur->offset >= cur->read_size)
			remove_node(&lst, &cur);
	}
	return (read_line);
}
