/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:06:43 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 13:06:47 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	copy_len;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len - start > len)
		copy_len = len;
	else
		copy_len = s_len - start;
	sub = malloc(sizeof(char) * (copy_len + 1));
	if (sub == NULL)
		return (NULL);
	ft_memcpy(sub, s + start, copy_len);
	sub[copy_len] = '\0';
	return (sub);
}
