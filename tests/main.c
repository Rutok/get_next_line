/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 00:40:12 by nboste            #+#    #+#             */
/*   Updated: 2016/12/02 03:31:53 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd = open(argv[argc - 1], O_RDONLY);
	char *str;
	int l;
	l = get_next_line(fd, &str);
	if (l >= 0)
	{
		do
		{
			ft_putendl(str);
			l = get_next_line(fd, &str);
			argc++;
		}
		while (l);
	}
	return (l);
}
