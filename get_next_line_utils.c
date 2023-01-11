/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttachi <ttachi@student.42tokyo.ja>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 23:03:00 by ttachi            #+#    #+#             */
/*   Updated: 2023/01/11 12:12:03 by ttachi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	count;

	count = 0;
	if (destsize == 0)
		return (ft_strlen(src));
	while (count < destsize - 1 && src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_len;
	size_t	src_len;

	if (dest == NULL)
		dest_len = 0;
	else
		dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= destsize)
		return (src_len + destsize);
	ft_strlcpy(dest + dest_len, src, destsize - dest_len);
	return (dest_len + src_len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new;

	len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s, len + 1);
	return (new);
}

char	*ft_strljoin(char *s1, char *s2, size_t head, size_t tail)
{
	size_t	s1_len;
	size_t	join_len;
	char	*result;

	if (s1 == NULL || *s1 == '\0')
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	join_len = tail - head;
	result = malloc(sizeof(char) * (s1_len + join_len + 1));
	if (result == NULL)
		return (NULL);
	if (s1 == NULL || s1[0] == '\0')
		ft_strlcpy(result, s2 + head, join_len + 1);
	else
	{
		ft_strlcpy(result, s1, s1_len + 1);
		ft_strlcat(result, s2 + head, s1_len + join_len + 1);
	}
	return (result);
}
