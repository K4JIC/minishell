/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:05:02 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 13:05:05 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_copy;
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	len_dst = 0;
	while (len_dst < size && dst[len_dst] != '\0')
		len_dst++;
	if (len_dst >= size)
		return (size + len_src);
	if (len_src + 1 < size - len_dst)
		len_copy = len_src;
	else
		len_copy = size - len_dst - 1;
	ft_memcpy(dst + len_dst, src, len_copy);
	dst[len_dst + len_copy] = '\0';
	return (len_dst + len_src);
}
