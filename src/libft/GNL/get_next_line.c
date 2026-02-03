/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:17:22 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/26 10:05:26 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_leftover(char *leftover)
{
	char	*new;
	char	*head_ptr;
	size_t	len_new;

	if (leftover == NULL)
		return (NULL);
	head_ptr = gnl_strchr(leftover, '\n');
	if (head_ptr == NULL)
	{
		free(leftover);
		return (NULL);
	}
	len_new = gnl_strlen(head_ptr + 1);
	new = malloc(sizeof(char) * (len_new + 1));
	if (new == NULL)
	{
		free(leftover);
		return (NULL);
	}
	gnl_strlcpy(new, head_ptr + 1, len_new + 1);
	free(leftover);
	return (new);
}

static char	*extract_line(char const *leftover)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (leftover == NULL || *leftover == '\0')
		return (NULL);
	len = 0;
	while (leftover[len] && leftover[len] != '\n')
		len++;
	if (leftover[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	free_all(char **leftover, char **buf)
{
	if (leftover != NULL)
	{
		free(*leftover);
		*leftover = NULL;
	}
	free(*buf);
	return (-1);
}

static int	read_one_line(int fd, char **leftover)
{
	char	*buf;
	ssize_t	read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (free_all(leftover, &buf));
	while (gnl_strchr(*leftover, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free_all(leftover, &buf));
		if (read_bytes == 0)
		{
			free(buf);
			return (0);
		}
		buf[read_bytes] = '\0';
		*leftover = gnl_strjoin(*leftover, buf);
		if (*leftover == NULL)
			return (free_all(leftover, &buf));
	}
	free(buf);
	return (1);
}

char	*ft_gnl(int fd)
{
	static char	*leftover = NULL;
	char		*line;
	char		*new_lo;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = read_one_line(fd, &leftover);
	if (status <= 0 && (leftover == NULL || *leftover == '\0'))
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = extract_line(leftover);
	if (line == NULL)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	new_lo = update_leftover(leftover);
	leftover = new_lo;
	return (line);
}
