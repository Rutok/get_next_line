/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:03:40 by nboste            #+#    #+#             */
/*   Updated: 2016/12/02 01:11:23 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

int		get_next_line(const int fd, char **line)
{
	static t_buffer	*buffer;
	char			*ret;
	char			*tmp;

	if (init_buffer(&buffer))
		return (-1);
	ret = NULL;
	if (buffer->remaining_data != NULL)
	{
		if (is_line_in_buffer(buffer->remaining_data, &tmp) >= 0)
		{
			if (!(ret = ft_strnew(tmp - buffer->data)))
				return (-1);
			ft_strncpy(ret, buffer->remaining_data, tmp - buffer->remaining_data);
			buffer->remaining_data = tmp + 1;
			*line = ret;
			if (*tmp == '\n')
				return (1);
			return (0);
		}
		if (!(ret = ft_strnew(BUFF_SIZE - (buffer->remaining_data - buffer->data))))
			return (-1);
		ft_strcpy(ret, buffer->remaining_data);
	}
	else if (!(ret = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (read(fd, (void *)buffer->data, BUFF_SIZE))
	{
		if ((tmp = ft_strchr(buffer->data, (int)'\n')) || (tmp = ft_strchr(buffer->data, EOF)))
		{
			buffer->remaining_data = NULL;
			if (*tmp == '\n')
				buffer->remaining_data = tmp + 1;
			*tmp = '\0';
			tmp = ret;
			ret = ft_strjoin(ret, buffer->data);
			free(tmp);
			*line = ret;
			if (buffer->remaining_data)
				return (1);
			return (0);
		}
		else
			ft_strjoin(ret, buffer->data);
	}
	return (0);
}

int		init_buffer(t_buffer **buffer)
{
	static int	call;
	if (!call)
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
		call++;
		return (0);
	}
	return (0);
}

int		is_line_in_buffer(char *buffer, char **loc)
{
	char *tmp;

	if ((tmp = ft_strchr(buffer, (int)'\n')) || (tmp = ft_strchr(buffer, EOF)))
	{
		*loc = tmp;
		if (*tmp == '\n')
			return (0);
		if (*tmp == EOF)
			return (1);
	}
	return (-1);
}
