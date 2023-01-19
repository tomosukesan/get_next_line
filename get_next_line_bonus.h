/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:03:13 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/19 17:49:59 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# define TRUE 1
# define FALSE 0
# define OPEN_MAX 256

typedef struct s_data
{
	char	*buf;
	ssize_t	i;
	size_t	buf_count;
	ssize_t	word_count;
	ssize_t	bs;
	char	*ret_val;
}	t_data;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
char	*ft_strljoin(char *s1, char *s2, size_t head, size_t tail);
void	*ft_free(char **p);

#endif
