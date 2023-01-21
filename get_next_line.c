/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.ja>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:02:41 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/20 21:55:09 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs);
static char		*make_line(t_data *data, size_t bs, size_t i);
static ssize_t	store_ret_val(t_data *data, size_t bs);
static char		judge_invalid_fd(int fd, t_data *data);

char	*get_next_line(int fd)
{
	static t_data	data;

	if (judge_invalid_fd(fd, &data))
		return (NULL);
	while (data.i < data.bs || data.bs == 0)
	{
		if (data.buf == NULL)
		{
			data.bs = ft_isread(fd, &data, BUFFER_SIZE);
			if (data.ret_val != NULL && data.bs == 0)
				return (make_line(&data, data.bs, 0));
			if (data.bs <= 0)
				break ;
		}
		if (data.buf[data.i] == '\n')
			return (make_line(&data, data.bs, (size_t)data.i));
		if (data.i == data.bs - 1)
		{
			data.i = store_ret_val(&data, data.bs);
			if (data.i == FALSE)
				break ;
		}
		data.i++;
	}
	return (NULL);
}

static char	judge_invalid_fd(int fd, t_data *data)
{
	if (!(0 <= fd && fd < OPEN_MAX))
		return (TRUE);
	data->ret_val = NULL;
	data->i = data->buf_count;
	return (FALSE);
}

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs)
{
	ssize_t	word_count;

	data->buf = (char *)malloc(sizeof(char) * bs);
	if (data->buf == NULL)
	{
		ft_free(&data->ret_val);
		return (-1);
	}
	word_count = read(fd, (void *)data->buf, bs);
	if (word_count <= 0)
		ft_free(&data->buf);
	return (word_count);
}

static char	*make_line(t_data *data, size_t bs, size_t i)
{
	char	*tmp;

	tmp = NULL;
	if (data->ret_val != NULL)
	{
		if (bs == 0)
			return (data->ret_val);
		tmp = ft_strljoin(data->ret_val, NULL, 0, 0);
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
	if (i == bs - 1)
		ft_free(&(data->buf));
	data->buf_count = (i + 1) * !(i == bs - 1);
	ft_free(&tmp);
	return (data->ret_val);
}

static ssize_t	store_ret_val(t_data *data, size_t bs)
{
	char	*tmp;

	tmp = NULL;
	if (data->ret_val != NULL)
	{
		tmp = ft_strljoin(data->ret_val, NULL, 0, 0);
		free(data->ret_val);
		if (tmp == NULL)
		{
			ft_free(&data->buf);
			return (FALSE);
		}
	}
	data->ret_val = ft_strljoin(tmp, data->buf, data->buf_count, bs);
	if (data->ret_val == NULL)
	{
		free(data->buf);
		ft_free(&tmp);
		ft_free(&data->ret_val);
		return (FALSE);
	}
	ft_free(&(data->buf));
	free(tmp);
	data->buf_count = 0;
	return (-1);
}
