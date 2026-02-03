/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:04:28 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 13:04:29 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len_s;
	char	*ptr;

	len_s = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len_s + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s, len_s + 1);
	return (ptr);
}
