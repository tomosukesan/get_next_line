/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.ja>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:02:41 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/16 22:22:39 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs);
static char		*make_line(t_data *data, size_t bs, size_t i);
static ssize_t	store_ret_val(t_data *data, size_t bs);
static void		*ft_free(char **p);

char	*get_next_line(int fd)
{
	static t_data	data;
	ssize_t			i;

	data.ret_val = NULL;
	i = data.buf_count;
	while (i < data.bs || data.bs == 0)
	{
		if ((size_t)i == data.buf_count)
		{
			data.bs = ft_isread(fd, &data, BUFFER_SIZE);
			if (data.ret_val != NULL && data.bs == 0)
				return (make_line(&data, 1, data.buf_count));
			if (data.bs <= 0)
				return (NULL);
		}
		if (data.buf[i] == '\n')
			break ;
		if (i == data.bs - 1)
		{
			i = store_ret_val(&data, data.bs);
			if (i == FALSE)
				return (NULL);
		}
		i++;
	}
	return (make_line(&data, data.bs, i));
}

static ssize_t	ft_isread(int fd, t_data *data, ssize_t bs)
{
	if (!(0 <= fd && fd <= FOPEN_MAX))
	{
		printf("come");
		return (-1);
	}
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
	data->buf_count = (i + 1) * !(i == bs - 1);
	if (i == bs - 1)
		free(data->buf);
	ft_free(&tmp);
	return (data->ret_val);
}

static ssize_t	store_ret_val(t_data *data, size_t bs)
{
	char	*tmp;

	tmp = NULL;
	if (data->ret_val != NULL)
	{
		tmp = ft_strdup(data->ret_val);
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
	free(data->buf);
	free(tmp);
	data->buf_count = 0;
	return (-1);
}

static void	*ft_free(char **p)
{
	if (*p != NULL)
		free(*p);
	*p = NULL;
	return (NULL);
}
