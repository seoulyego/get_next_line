/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:09:54 by yeongo            #+#    #+#             */
/*   Updated: 2022/06/24 20:05:45 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	return (SUCCESS);
}

int	get_line(char **dst, t_list *node)
{
	char	*result;
	ssize_t	m_size;
	ssize_t	index;

	m_size = line_len(*dst, 0, 0) + line_len(node->buffer, node->offset, 1);
	result = ft_calloc(m_size + 1, sizeof(char));
	if (result == NULL)
		return (ERROR);
	index = 0;
	while (*dst != NULL && index < node->read_size)
	{
		result[index] = (*dst)[index];
		index++;
	}
	while (index < m_size && node->offset < BUFFER_SIZE)
	{
		result[index] = node->buffer[node->offset];
		node->offset++;
		index++;
	}
	if (*dst != NULL)
		free(*dst);
	*dst = result;
	return (SUCCESS);
}

char	*fail_to_read_fd(int result, char *str, t_list **lst, t_list *cur)
{
	if (cur != NULL)
	{
		remove_node(lst, cur);
		cur = NULL;
	}
	if (result == ERROR)
		return (NULL);
	return (str);
}

char	*fail_to_get_line(char **str)
{
	if (*str != NULL)
		free(*str);
	return (NULL);
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
	while (nl_in_buffer(read_line, line_len(read_line, 0, 1)) == NO_NL)
	{
		if (cur == NULL)
		{
			result = read_fd(&lst, &cur, fd);
			if (result != SUCCESS)
				return (fail_to_read_fd(result, read_line, &lst, cur));
		}
		if (cur->offset != cur->read_size)
			result = get_line(&read_line, cur);
		if (result != SUCCESS)
			return (fail_to_get_line(&read_line));
		if (cur->offset == cur->read_size - 1)
		{
			remove_node(&lst, cur);
			cur = NULL;
		}
	}
	return (read_line);
}
