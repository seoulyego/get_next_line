/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:09:58 by yeongo            #+#    #+#             */
/*   Updated: 2022/07/20 09:11:35 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define SUCCESS 1
# define NO_NL -1
# define NO_READ -2
# define ERROR -3
# define READ_EOF -4

typedef struct s_list	t_list;

struct s_list
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_fd;
	ssize_t	read_size;
	ssize_t	offset;
	t_list	*next;
};

size_t	line_len(char *str, size_t offset, int nl_check);
t_list	*ft_lstadd_back(t_list **lst, int fd);
t_list	*remove_node(t_list **lst, t_list **node_ref);
ssize_t	nl_in_buffer(char *buffer, ssize_t size);
int		read_fd(t_list **lst, t_list **cur, int fd);
int		get_line(char **dst, t_list *node);
char	*fail_to_read_fd(int result, char *str, t_list **lst, t_list **cur);
char	*fail_to_get_line(t_list **lst, char **str);
char	*get_next_line(int fd);

#endif
