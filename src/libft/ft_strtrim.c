/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:06:31 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 13:06:34 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const*set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	len_copy;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && is_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_set(s1[end - 1], set))
		end--;
	len_copy = end - start;
	trim = malloc(sizeof(char) * (len_copy + 1));
	if (trim == NULL)
		return (NULL);
	ft_memcpy(trim, s1 + start, len_copy);
	trim[len_copy] = '\0';
	return (trim);
}
