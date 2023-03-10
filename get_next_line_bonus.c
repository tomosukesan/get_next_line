/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.ja>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:02:41 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/22 07:14:22 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs);
static char		*make_line(t_data *data, size_t bs, size_t i);
static ssize_t	store_ret_val(t_data *data, size_t bs);
static char		judge_invalid_fd(int fd, t_data *data);

char	*get_next_line(int fd)
{
	static t_data	data[OPEN_MAX];

	if (judge_invalid_fd(fd, &data[fd]))
		return (NULL);
	while (data[fd].i < data[fd].bs || data[fd].bs == 0)
	{
		if (data[fd].buf == NULL)
		{
			data[fd].bs = ft_isread(fd, &data[fd], BUFFER_SIZE);
			if (data[fd].ret_val != NULL && data[fd].bs == 0)
				return (make_line(&data[fd], data[fd].bs, 0));
			if (data[fd].bs <= 0)
				break ;
		}
		if (data[fd].buf[data[fd].i] == '\n')
			return (make_line(&data[fd], data[fd].bs, (size_t)data[fd].i));
		if (data[fd].i == data[fd].bs - 1)
		{
			data[fd].i = store_ret_val(&data[fd], data[fd].bs);
			if (data[fd].i == FALSE)
				break ;
		}
		data[fd].i++;
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
	data->buf_count = (i + 1) * !(i == bs - 1);
	if (i == bs - 1)
		ft_free(&(data->buf));
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
