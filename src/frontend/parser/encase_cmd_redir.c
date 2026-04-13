/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encase_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 23:10:11 by tozaki            #+#    #+#             */
/*   Updated: 2026/04/06 23:10:13 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	convert_redir(t_minishell *sh, t_cmd_base **parent, t_token_lr lr)
{
	(void)sh;
	(void)parent;
	(void)lr;

	/* TODO: implement redir handling
	 * - validate left/right presence
	 * - extract filename from right
	 * - create cmd_redir node
	 * - recursively process left side
	 */
	return (SUCCESS);
}
