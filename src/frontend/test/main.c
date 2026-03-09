/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:17:54 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/03 19:22:12 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

void	token_list_debug(void)
{
	printf("--token_list_debug--\n");
	t_token	*fir;
	t_token	*sec;
	t_token	*thi;
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = malloc(4);
	str2 = malloc(4);
	str3 = malloc(4);
	ft_strlcpy(str1, "fir", 4);
	ft_strlcpy(str2, "sec", 4);
	ft_strlcpy(str3, "thi", 4);
	str1[3] = '\0';
	str2[3] = '\0';
	str3[3] = '\0';
	fir = create_token(str1);
	sec = create_token(str2);
	thi = create_token(str3);
	add_token_last(fir, sec);
	add_token_last(fir, thi);
	print_all_token(fir);
	free_all_token(fir);
	printf("--end--\n");
}

void	tokenizer_debug(char *s)
{
	printf("--tokenizer_debug--\n");
	t_token	*head;

	printf("line = %s\n", s);
	head = tokenizer(s);
	set_all_lavel(head);
	print_all_token(head);
	free_all_token(head);
	printf("--end--\n");
}

#ifdef DEBUG
int	main(void)
{
	char	*s = "aaa bbb 'aaa bbb'<< ccc|ddd>outputs/log";
	char	*s2 = "aaa bbb 'aaa 'bbb<< ccc|ddd>outputs/log";

	token_list_debug();
	tokenizer_debug(s);
	tokenizer_debug(s2);
	return (0);
}
#endif
