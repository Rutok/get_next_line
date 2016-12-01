/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:03:32 by nboste            #+#    #+#             */
/*   Updated: 2016/12/02 00:03:15 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32
# define EOF -1

typedef struct	s_buffer
{
	char	*data;
	char	*remaining_data;
	size_t	data_length;
	size_t	remaining_data_length;
}				t_buffer;

int		get_next_line(const int fd, char **line);

int		init_buffer(t_buffer *buffer);

// This function returns 0 or 1 if a \n or EOF is in buffer, < 0 means both no
// loc = found charactter addr
int		is_line_in_buffer(char *buffer, char **loc);

#endif
