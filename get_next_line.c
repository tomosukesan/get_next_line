/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.ja>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:02:41 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/15 22:32:49 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs);
static char		*make_line(t_data *data, size_t bs, size_t i);
static char		*store_ret_val(int fd, t_data *data, size_t bs);
static void		*ft_free(char **p);

char	*get_next_line(int fd)
{
	static t_data	data;
	ssize_t			bs;
	ssize_t			i;

	if (data.return_line)
	{
		data.ret_val = NULL;
		data.return_line = FALSE;
	}
	bs = ft_isread(fd, &data, BUFFER_SIZE);
	if (data.ret_val != NULL && bs == 0)
		return (make_line(&data, bs, data.buf_count));
	if (bs <= 0)
		return (NULL);
	i = data.buf_count;
	while (i < bs)
	{
		if (data.buf[i] == '\n')
			return (make_line(&data, bs, i));
		i++;
	}
	return (store_ret_val(fd, &data, bs));
}

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs)
{
	if (data->buf_count == 0)
	{
		data->buf = (char *)malloc(sizeof(char) * bs);
		if (data->buf == NULL)
		{
			ft_free(&data->ret_val);
			return (-1);
		}
		data->word_count = read(fd, (void *)data->buf, bs);
		if (data->word_count <= 0)
			ft_free(&data->buf);
	}
	return (data->word_count);
}

static char	*make_line(t_data *data, size_t bs, size_t i)
{
	char	*tmp;

	tmp = NULL;
	if (data->ret_val != NULL)
	{
		tmp = ft_strdup(data->ret_val);
		free(data->ret_val);
		if (tmp == NULL)
			return (ft_free(&data->buf));
	}
	data->ret_val = ft_strljoin(tmp, data->buf, data->buf_count, i + 1);
	if (data->ret_val == NULL)
	{
		free(data->buf);
		ft_free(&tmp);
		return (ft_free(&data->ret_val));
	}
	data->buf_count = (i + 1) * (i != bs - 1);
	if (i == bs - 1)
		free(data->buf);
	ft_free(&tmp);
	data->return_line = TRUE;
	return (data->ret_val);
}

static char	*store_ret_val(int fd, t_data *data, size_t bs)
{
	char	*tmp;

	tmp = NULL;
	if (data->ret_val != NULL)
	{
		tmp = ft_strdup(data->ret_val);
		free(data->ret_val);
		if (tmp == NULL)
			return (ft_free(&data->buf));
	}
	data->ret_val = ft_strljoin(tmp, data->buf, data->buf_count, bs);
	if (data->ret_val == NULL)
	{
		free(data->buf);
		ft_free(&tmp);
		return (ft_free(&data->ret_val));
	}
	free(data->buf);
	free(tmp);
	data->buf_count = 0;
	return (get_next_line(fd));
}

static void	*ft_free(char **p)
{
	if (*p != NULL)
		free(*p);
	*p = NULL;
	return (NULL);
}
