/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.ja>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:02:41 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/15 00:48:40 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_isread(int fd, t_data *data, size_t *bs);
static char	*make_line(t_data *data, size_t bs, size_t i);
static char	*store_ret_val(int fd, t_data *data, size_t bs);
static void	*ft_free(void *p);

char	*get_next_line(int fd)
{
	static t_data	data;
	size_t			bs;
	size_t			i;

	bs = BUFFER_SIZE;
	if (data.return_line)
	{
		data.ret_val = NULL;
		data.return_line = FALSE;
	}
	if (bs == 0 || ft_isread(fd, &data, &bs) == NULL)
		return (NULL);
	if (data.buf_count != 0 && data.eof_flag)
		bs = data.word_count;
	i = data.buf_count;
	if (data.word_count == 0 && data.eof_flag)
		return (data.ret_val);
	while (i < bs)
	{
		if (data.buf[i] == '\n' || (data.eof_flag && i == bs - 1))
			return (make_line(&data, bs, i));
		i++;
	}
	return (store_ret_val(fd, &data, bs));
}

static void	*ft_isread(int fd, t_data *data, size_t *bs)
{
	if (data->buf_count == 0)
	{
		if (data->eof_flag)
			return (NULL);
		data->buf = (char *)malloc(sizeof(char) * (*bs));
		if (data->buf == NULL)
			return (ft_free(data->ret_val));
		data->word_count = read(fd, (void *)data->buf, *bs);
		if (data->word_count == 0 && data->ret_val != NULL)
		{
			data->eof_flag = TRUE;
			free(data->buf);
		}
		else if (data->word_count < 0)
		{
			free(data->buf);
			return (ft_free(data->ret_val));
		}
		else if ((size_t)data->word_count == 0)
		{
			data->eof_flag = TRUE;
			*bs = data->word_count;
		}
	}
	return ((void *)bs);
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
			return (ft_free(data->buf));
	}
	data->ret_val = ft_strljoin(tmp, data->buf, data->buf_count, i + 1);
	if (data->ret_val == NULL)
	{
		free(data->buf);
		ft_free(tmp);
		return (ft_free(data->ret_val));
	}
	data->buf_count = (i + 1) * (i != bs - 1);
	if (i == bs - 1)
		free(data->buf);
	ft_free(tmp);
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
			return (ft_free(data->buf));
	}
	data->ret_val = ft_strljoin(tmp, data->buf, data->buf_count, bs);
	if (data->ret_val == NULL)
	{
		free(data->buf);
		ft_free(tmp);
		return (ft_free(data->ret_val));
	}
	free(data->buf);
	free(tmp);
	data->buf_count = 0;
	return (get_next_line(fd));
}

static void	*ft_free(void *p)
{
	if (p != NULL)
		free(p);
	return (NULL);
}
