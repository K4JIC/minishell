#include "minishell.h"

static int	ensure_buf_capacity(t_dynamic_str *buf, int add_len)
{
	int		newcapa;
	int		need;
	char	*newstr;
	size_t	copied;

	if (!buf || !buf->str || add_len < 0)
		return (FAILURE);
	need = buf->len + add_len + 1;
	if (need <= buf->capa)
		return (SUCCESS);
	newcapa = buf->capa;
	while (newcapa < need)
		newcapa *= 2;
	newstr = ft_calloc(newcapa, 1);
	if (!newstr)
		return (FAILURE);
	copied = ft_strlcpy(newstr, buf->str, newcapa);
	if (copied >= (size_t)newcapa)
		return (free(newstr), FAILURE);
	free(buf->str);
	buf->str = newstr;
	buf->capa = newcapa;
	return (SUCCESS);
}

t_dynamic_str	*init_buf(void)
{
	t_dynamic_str	*buf;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_calloc(1, sizeof(t_dynamic_str));
	if (!buf)
		return (NULL);
	buf->str = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buf->str)
		return (free(buf), NULL);
	buf->capa = BUFFER_SIZE;
	return (buf);
}

void	free_dynamic_str(t_dynamic_str *buf)
{
	if (!buf)
		return ;
	if (buf->str)
		free(buf->str);
	free(buf);
}

int	putnstr_buf(t_dynamic_str *buf, const char *str, int n)
{
	if (!buf || !buf->str || !str)
		return (FAILURE);
	if (ensure_buf_capacity(buf, n) == FAILURE)
		return (FAILURE);
	ft_memcpy(buf->str + buf->len, str, n);
	buf->len += n;
	buf->str[buf->len] = '\0';
	return (SUCCESS);
}

int	putstr_buf(t_dynamic_str *buf, const char *str)
{
	int	len;

	len = ft_strlen(str);
	return (putnstr_buf(buf, str, len));
}
