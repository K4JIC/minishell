#include "minishell.h"

static int	str_to_ll(char *str, int sign, long long *num)
{
	long long	result;

	result = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if (sign == 1 && (result > (LLONG_MAX - (*str - '0')) / 10))
			return (0);
		if (sign == -1 && (result > (-(LLONG_MIN + (*str - '0'))) / 10))
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	*num = result * sign;
	return (1);
}

static int	is_numeric_arg(char *str, long long *num)
{
	int	sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		return (0);
	return (str_to_ll(str, sign, num));
}

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	ft_exit(t_cmd *cmd, t_minishell *ms)
{
	long long	num;

	ft_putstr_fd("exit\n", 2);
	if (cmd->args[1] == NULL)
	{
		ms->should_exit = 1;
		return (ms->exit_status);
	}
	if (!is_numeric_arg(cmd->args[1], &num))
	{
		print_numeric_error(cmd->args[1]);
		ms->exit_status = 2;
		ms->should_exit = 1;
		return (2);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (FAILURE);
	}
	ms->exit_status = (int)(num & 255);
	ms->should_exit = 1;
	return (ms->exit_status);
}
