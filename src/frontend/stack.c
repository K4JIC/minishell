/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozaki <tozaki@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 23:26:09 by tozaki            #+#    #+#             */
/*   Updated: 2026/02/21 16:41:51 by tozaki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include "libft.h"

typedef struct s_stack_array
{
	char	*content;
	ssize_t	top;
	size_t	capacity;
}	t_stack_array;

t_stack_array	init_stack(size_t stack_size)
{
	t_stack_array	stack;

	stack.content = (char *)malloc((stack_size + 1) * sizeof(char));
	if (!stack.content)
	{
		stack.top = -1;
		stack.capacity = 0;
		return (stack);
	}
	//ft_bzero(stack->content, stack_size + 1);
	bzero(stack.content, stack_size + 1);
	stack.top = -1;
	stack.capacity = stack_size;
	return (stack);
}

t_stack_array	*realloc_stack(t_stack_array *stack)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * stack->capacity * 2);
	if (!tmp)
		return (NULL);
	stack->capacity *= 2;
	//if (ft_strcpy(tmp, stack->content) == NULL)
	if (strcpy(tmp, stack->content) == NULL)
	{
		free(tmp);
		return (NULL);
	}
	free(stack->content);
	stack->content = tmp;
	return (stack);
}

t_stack_array	*push_stack(t_stack_array *stack, char new)
{
	if (!stack)
		return (NULL);
	stack->top++;
	if (stack->top + 1 >= (ssize_t)stack->capacity)
	{
		stack = realloc_stack(stack);
		if (!stack)
			return (NULL);
	}
	stack->content[stack->top] = new;
	stack->content[stack->top + 1] = '\0';
	return (stack);
}

char	pop_stack(t_stack_array *stack)
{
	char	poped;

	if (!stack || stack->top == -1)
		return (0);
	poped = stack->content[stack->top];
	stack->content[stack->top] = '\0';
	stack->top--;
	return (poped);
}

int	main(void)
{
	t_stack_array	stack;

	stack = init_stack(2);
	push_stack(&stack, '(');
	printf("%c\n", stack.content[stack.top]);
	printf("%s\n", stack.content);
	push_stack(&stack, ')');
	printf("%c\n", stack.content[stack.top]);
	printf("%s\n", stack.content);
	pop_stack(&stack);
	printf("%s\n", stack.content);
	free(stack.content);
	return (0);
}
