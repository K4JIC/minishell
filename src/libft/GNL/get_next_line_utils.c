/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:17:51 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/23 17:52:06 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;
	int	s_len;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = gnl_strlen(s);
	while (i <= s_len)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	copy_len;
	size_t	src_len;

	src_len = gnl_strlen(src);
	if (dsize == 0)
		return (src_len);
	copy_len = 0;
	if (src_len + 1 < dsize)
		copy_len = src_len;
	else if (dsize != 0)
		copy_len = dsize - 1;
	gnl_memcpy(dst, src, copy_len);
	dst[copy_len] = '\0';
	return (src_len);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL)
	{
		s1 = malloc(1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (s2 == NULL)
		return (NULL);
	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	join = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (join == NULL)
	{
		free(s1);
		return (NULL);
	}
	gnl_memcpy(join, s1, len_s1);
	gnl_memcpy(join + len_s1, s2, len_s2 + 1);
	free(s1);
	return (join);
}
