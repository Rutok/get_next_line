/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:03:40 by nboste            #+#    #+#             */
/*   Updated: 2016/12/02 04:18:35 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

int		get_next_line(const int fd, char **line)
{
	static t_buffer	*buffer;
	char			*ret;
	char			*tmp;
	int				nb_read;

	if (!(line) || fd <= 0 || init_buffer(&buffer))
		return (-1);
	ret = NULL;
	if (buffer->remaining_data != NULL)
	{
		if ((tmp = ft_strchr(buffer->remaining_data, (int)'\n')))
		{
			if (!(ret = ft_strnew(tmp - buffer->remaining_data)))
				return (-1);
			ft_strncpy(ret, buffer->remaining_data, tmp - buffer->remaining_data);
			buffer->remaining_data = tmp + 1;
			*line = ret;
			return (1);
		}
		else if (buffer->eof)
		{
			if (!(ret = ft_strdup(buffer->remaining_data)))
				return (-1);
			*line = ret;
			reset_buffer(buffer);
			return (0);
		}
		else if (!(ret = ft_strnew(BUFF_SIZE - (buffer->remaining_data - buffer->data))))
			return (-1);
		ft_strcpy(ret, buffer->remaining_data);
	}
	else if (!(ret = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((nb_read = read(fd, (void *)buffer->data, BUFF_SIZE)) >= 0)
	{
		buffer->remaining_data = NULL;
		if ((tmp = ft_strchr(buffer->data, (int)'\n')))
		{
			buffer->remaining_data = tmp + 1;
			*tmp = '\0';
		}
		if (nb_read < BUFF_SIZE)
		{
			buffer->data[nb_read] = '\0';
			buffer->eof = 1;
		}
		tmp = ret;
		ret = ft_strjoin(ret, buffer->data);
		free(tmp);
		if (buffer->remaining_data != NULL || nb_read < BUFF_SIZE)
		{
			*line = ret;
			return (buffer->remaining_data != NULL);
		}
	}
	return (-1);
}

int		init_buffer(t_buffer **buffer)
{
	if (!*buffer)
	{
		if (!(*buffer = (t_buffer *)malloc(sizeof(t_buffer))))
			return (1);
		if (!((*buffer)->data = ft_strnew(BUFF_SIZE)))
		{
			free(*buffer);
			return (1);
		}
		(*buffer)->remaining_data = NULL;
		(*buffer)->data_length = BUFF_SIZE;
		(*buffer)->remaining_data_length = 0;
		(*buffer)->eof = 0;
		return (0);
	}
	return (0);
}

void	reset_buffer(t_buffer *buffer)
{
	buffer->remaining_data = NULL;
	buffer->eof = 0;
}
