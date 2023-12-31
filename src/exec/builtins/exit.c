/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:22:57 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/04 14:07:50 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	is_longlong(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 18)
	{
		if (len > 19)
		{
			if (str[0] == '+')
			{
				if (ft_strncmp(str, "+9223372036854775807", 20) > 0)
					return (0);
			}
			else if (str[0] == '-')
			{
				if (ft_strncmp(str, "-9223372036854775808", 20) > 0)
					return (0);
			}
			else
				return (0);
		}
		else
			if (ft_strncmp(str, "9223372036854775807", 20) > 0)
				return (0);
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' )
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

//handle arguments
int	exec_exit(t_data *data, t_node *node)
{
	unsigned char	exit_val;

	exit_val = g_err_code;
	if (isatty(0) == 1 && isatty(1) == 1)
		ft_putstr_fd("exit\n", 1);
	if (node->arguments[1])
	{
		if (is_number(node->arguments[1])
			&& is_longlong(node->arguments[1]))
			exit_val = (unsigned char)
				ft_atoll(node->arguments[1]) % 256;
		else
			exit_all(data, ferrnl("exit", node->arguments[1],
					"numeric argument required", 2));
		if (node->arguments[2])
			return (errnl(1, "minishell: exit: too many arguments"));
	}
	return (exit_all(data, exit_val));
}
