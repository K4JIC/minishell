/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yikebata <yikebata@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:17:39 by yikebata          #+#    #+#             */
/*   Updated: 2025/11/26 10:05:42 by yikebata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# if BUFFER_SIZE<=0
#  error "BUFFER_SIZE shoul be greater than 1."
# endif

# include <unistd.h>
# include <stdlib.h>

//get_next_line.c
char	*ft_gnl(int fd);

//get_next_line_utils.c
size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
void	*gnl_memcpy(void *dest, const void *src, size_t n);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dsize);
char	*gnl_strjoin(char *s1, char *s2);

#endif
