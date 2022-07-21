/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:10:02 by yeongo            #+#    #+#             */
/*   Updated: 2022/07/21 20:54:13 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
