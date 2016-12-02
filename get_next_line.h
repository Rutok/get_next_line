/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:03:32 by nboste            #+#    #+#             */
/*   Updated: 2016/12/02 04:10:43 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFF_SIZE 32

typedef struct	s_buffer
{
	char	*data;
	char	*remaining_data;
	char	*last;
	size_t	data_length;
	size_t	remaining_data_length;
	int		eof;
}				t_buffer;

int				get_next_line(const int fd, char **line);

int				init_buffer(t_buffer **buffer);

int				is_line_in_buffer(char *buffer, char **loc);

void			reset_buffer(t_buffer *buffer);

#endif
