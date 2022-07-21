/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:09:54 by yeongo            #+#    #+#             */
/*   Updated: 2022/07/21 20:17:21 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*fail_to_read_fd(int result, char *str, t_list **lst, t_list **cur)
{
	if (*cur != NULL)
		remove_node(lst, cur);
	if (result == ERROR)
		return (NULL);
	return (str);
}

char	*fail_to_get_line(t_list **lst, char **str)
{
	t_list	*cur;

	if (*lst != NULL)
	{
		cur = *lst;
		while (cur != NULL)
		{
			*lst = cur->next;
			free(cur);
			cur = *lst;
		}
	}
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
		else
			remove_node(&lst, &cur);
	}
	return (read_line);
}
