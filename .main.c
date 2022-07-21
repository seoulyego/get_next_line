/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:50:42 by yeongo            #+#    #+#             */
/*   Updated: 2022/07/11 20:18:50 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

void	check_leaks(void)
{
	system("leaks a.out");
}

int	main(void)
{
	int fd = open("variable_nls.txt", O_RDONLY);
	char *str;

	//atexit(check_leaks);
	str = get_next_line(fd);
	while (str)
	{
		printf("str : %s\n", str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}
