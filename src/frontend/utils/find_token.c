#include "tokenizer.h"

static int	get_operator_len(char *s)
{
	if (ft_strncmp(";;s", s, 3) == 0)
		return (3);
	if (s[0] == s[1] && ft_strchr("&|;<>", s[0]))
		return (2);
	if (ft_strncmp("|&", s, 2) == 0 || ft_strncmp(";&", s, 2) == 0)
		return (2);
	if (ft_strchr("&|;<>()=", s[0]))
		return (1);
	return (NO_OPERATOR);
}

static int	get_word_len(char *p)
{
	int	len;
	int	quote_len;

	len = 0;
	while (p[len] && !ismeta(p[len]) && !ismsspace(p[len]))
	{
		if (isquote(p[len]))
		{
			quote_len = get_quoted_string_len(&p[len]);
			if (quote_len == NO_CLOSE_QUOTE)
				return (NO_CLOSE_QUOTE);
			len += quote_len;
		}
		else
			len++;
	}
	return (len);
}

int	get_one_token_len(char *p)
{
	int		len;

	if (!*p)
		return (0);
	else if (ismeta(*p))
		len = get_operator_len(p);
	else
		len = get_word_len(p);
	return (len);
}
