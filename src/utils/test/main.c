#include "ms_utils.h"
#include <stdio.h>

#ifdef MSMALLOC
int	main(void)
{
	char	*a;
	char	*b;

	a = msmalloc(1);
	b = msmalloc(2);
	ft_strlcpy(b, "b\n", 2);
	ft_printf("%s\n", b);
	msfree(a);
	msfree(b);
	return (0);
}
#endif

#ifdef QUOTE
int	main(void)
{
	/* ismeta */
	ft_printf("=== ismeta ===\n");
	ft_printf("ismeta('|')  = %d (expect 1)\n", ismeta('|'));
	ft_printf("ismeta(';')  = %d (expect 1)\n", ismeta(';'));
	ft_printf("ismeta('>')  = %d (expect 1)\n", ismeta('>'));
	ft_printf("ismeta('a')  = %d (expect 0)\n", ismeta('a'));
	ft_printf("ismeta(' ')  = %d (expect 0)\n", ismeta(' '));

	/* isquote */
	ft_printf("=== isquote ===\n");
	ft_printf("isquote('\"') = %d (expect 1)\n", isquote('"'));
	ft_printf("isquote('\\'') = %d (expect 1)\n", isquote('\''));
	ft_printf("isquote('a')  = %d (expect 0)\n", isquote('a'));

	/* ismsspace */
	ft_printf("=== ismsspace ===\n");
	ft_printf("ismsspace(' ')  = %d (expect 1)\n", ismsspace(' '));
	ft_printf("ismsspace('\\t') = %d (expect 1)\n", ismsspace('\t'));
	ft_printf("ismsspace('a')  = %d (expect 0)\n", ismsspace('a'));

	/* get_quoted_string_len */
	ft_printf("=== get_quoted_string_len ===\n");
	ft_printf("\"\\\"hello\\\"\"  = %d (expect 7)\n", get_quoted_string_len("\"hello\""));
	ft_printf("\"'world'\"   = %d (expect 7)\n", get_quoted_string_len("'world'"));
	ft_printf("\"\\\"no close\" = %d (expect %d)\n", get_quoted_string_len("\"no close"), NO_CLOSE_QUOTE, NO_CLOSE_QUOTE);
	ft_printf("\"hello\"      = %d (expect %d)\n", get_quoted_string_len("hello"), NO_QUOTE, NO_QUOTE);
	ft_printf("NULL         = %d (expect -1)\n", get_quoted_string_len(NULL));
	ft_printf("empty string = %d (expect -1)\n", get_quoted_string_len(""));

	return (0);
}
#endif

#ifdef LIST
typedef struct s_node
{
	t_head_list	head;
	int			value;
}	t_node;

static void	*print_node(void *ptr)
{
	t_node	*node;

	node = (t_node *)ptr;
	ft_printf("  node value = %d\n", node->value);
	return (ptr);
}

int	main(void)
{
	t_node	nodes[4];
	int		i;

	/* initialise nodes */
	i = 0;
	while (i < 4)
	{
		nodes[i].head.prev = NULL;
		nodes[i].head.next = NULL;
		nodes[i].value = i * 10;
		i++;
	}

	/* add_next_node: build a chain 0 -> 1 -> 2 -> 3 */
	ft_printf("=== add_next_node ===\n");
	add_next_node(&nodes[0].head, &nodes[1].head);
	add_next_node(&nodes[1].head, &nodes[2].head);
	add_next_node(&nodes[2].head, &nodes[3].head);

	/* get_last_node */
	ft_printf("=== get_last_node ===\n");
	{
		t_head_list	*last;
		t_node		*last_node;

		last = get_last_node(&nodes[0].head);
		last_node = (t_node *)last;
		ft_printf("last node value = %d (expect 30)\n", last_node->value);
	}

	/* apply_func */
	ft_printf("=== apply_func ===\n");
	{
		int	result;

		result = apply_func(&nodes[0].head, print_node);
		ft_printf("apply_func returned %d (expect %d)\n", result, SUCCESS);
	}

	/* apply_func with NULL head */
	ft_printf("=== apply_func NULL ===\n");
	{
		int	result;

		result = apply_func(NULL, print_node);
		ft_printf("apply_func(NULL) returned %d (expect %d)\n", result, FAILURE);
	}

	return (0);
}
#endif
