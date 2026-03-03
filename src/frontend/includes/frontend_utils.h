/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:37:02 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/03 19:20:33 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRONTEND_UTILS_H
# define FRONTEND_UTILS_H

typedef enum s_tokenize_error
{
	NO_QUOTE=-1,
	NO_CLOSE=-2,
	NO_OPERATOR=-3
}	t_tokenize_error;

char	*ismeta(char c);
int		isquote(const char c);
int		get_quoted_string_len(char *p);
int		get_one_token_len(char *p);

int		print_error_msg(char *msg);

#endif
