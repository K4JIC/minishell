/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 13:06:50 by tozaki            #+#    #+#             */
/*   Updated: 2026/03/03 18:53:56 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_btree
{
	void			*item;
	struct s_btree	*right;
	struct s_btree	*left;
}	t_btree;

t_btree	*btree_create_node(void *item)
{
	t_btree	*new;

	new = (t_btree *)malloc(sizeof(t_btree));
	if (!new)
		return (NULL);
	new->content = content;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_btree	*btree_insert_data(t_btree **root, void *item, int (*cmpf)(void *, void *))
{
	if (!(*root))
	{
		*root = btree_create_node(item);
		if (!(*root))
			return (NULL);
		return ;
	}
	if (cmpf((*root)->item, item) >= 0)
	{
		if (!btree_insert_data(&(*root)->left, item, cmpf));
			return (NULL);
	}
	else
	{
		if (!btree_insert_data(&(*root)->right, item, cmpf));
			return (NULL);
	}
}

