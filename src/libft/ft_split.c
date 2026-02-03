/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:04:06 by yikebata          #+#    #+#             */
/*   Updated: 2025/10/19 13:04:08 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_deli(char c, char deli)
{
	return (c == deli || c == '\0');
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s != '\0')
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	**free_all(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
	return (NULL);
}

static char	**do_split(char **splits, char const *s, char c, size_t word_count)
{
	size_t	i;
	size_t	word_start;
	size_t	word_len;

	i = 0;
	word_start = 0;
	while (i < word_count)
	{
		while (s[word_start] == c)
			word_start++;
		word_len = 0;
		while (!is_deli(s[word_start + word_len], c))
			word_len++;
		splits[i] = ft_substr(s, word_start, word_len);
		if (splits[i] == NULL)
			return (free_all(splits));
		word_start = word_start + word_len;
		i++;
	}
	splits[word_count] = NULL;
	return (splits);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	size_t	word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	splits = malloc(sizeof(char *) * (word_count + 1));
	if (splits == NULL)
		return (NULL);
	return (do_split(splits, s, c, word_count));
}
