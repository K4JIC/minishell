/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:14:29 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/03 19:19:45 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	child_fatal(const char *msg, int *fds, size_t n)
{
	size_t	i;

	perror(msg);
	while (i < n)
	{
		close()
	}
}
