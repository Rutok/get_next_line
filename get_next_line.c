/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboste <nboste@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:03:40 by nboste            #+#    #+#             */
/*   Updated: 2016/12/04 02:11:10 by nboste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

void	print_buffer(t_buffer *buffer)
{
	ft_putstr("FD: ");
	ft_putnbr(buffer->fd);
	ft_putendl(".");
	ft_putstr("strlenremain: ");
	if (buffer->remaining_data)
		ft_putnbr(ft_strlen(buffer->remaining_data));
	else
		ft_putstr("NULL");
	ft_putendl(".");
	ft_putstr("EOF:");
	ft_putnbr(buffer->eof);
	ft_putendl(".");
	ft_putstr("Buffer Data: ");
	ft_putnbr(ft_strlen(buffer->data));
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*l_buffers;
	t_buffer		*buffer;
	char			*ret;
	int				nb_read;

	buffer = get_buffer(&l_buffers, fd);
	if (!(ret = ft_strnew(0)))
		return (-1);
	nb_read = -1;
	if (buffer->eof && buffer->remaining_data == NULL)
		return (0);
	do
	{
		if (nb_read != -1)
		{
			buffer->last = buffer->data + nb_read - 1;
			buffer->remaining_data = buffer->data;
		}
		if (nb_read < BUFF_SIZE && nb_read != -1)
			buffer->eof = 1;
		if (process_buffer(&buffer, &ret))
		{
			*line = ret;
			return (1);
		}
	}
	while ((nb_read = read(fd, (void *)buffer->data, BUFF_SIZE)) >= 0);
	return (-1);
}

t_buffer	*get_buffer(t_list **buffers, int fd)
{
	t_list *tmp;
	t_buffer *buffer;

	tmp = *buffers;
	while (tmp)
	{
		if (((t_buffer *)(tmp->content))->fd == fd)
			return ((t_buffer *)(tmp->content));
		tmp = tmp->next;
	}
	if (!(buffer = (t_buffer *)malloc(sizeof(t_buffer))))
		return (NULL);
	if (!(buffer->data = ft_strnew(BUFF_SIZE)))
	{
		free(buffer);
		return (NULL);
	}
	buffer->remaining_data = NULL;
	buffer->fd = fd;
	buffer->last = NULL;
	buffer->eof = 0;
	ft_lstadd(buffers, ft_lstnew((void *)buffer, sizeof(t_buffer)));
	return ((t_buffer *)(*buffers)->content);
}

int		process_buffer(t_buffer **buffer, char **ret)
{
	char *tmp;
	char *rem;

	if ((*buffer)->remaining_data != NULL)
	{
		rem = (*buffer)->remaining_data;
		if ((tmp = ft_strchr((*buffer)->remaining_data, (int)'\n')))
		{
			*tmp = '\0';
			(*buffer)->remaining_data = tmp + 1;
			if (tmp + 1 > (*buffer)->last)
				(*buffer)->remaining_data = NULL;
		}
		else
		{
			(*buffer)->remaining_data = NULL;
		}
		tmp = *ret;
		if (!(*ret = ft_strjoin(*ret, rem)))
			return (0);
		free(tmp);
		if ((*buffer)->remaining_data != NULL || ((*buffer)->eof && (*buffer)->remaining_data == NULL))
			return (1);
		else
			return (0);
	}
	return (0);
}
