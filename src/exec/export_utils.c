/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:44:59 by elrichar          #+#    #+#             */
/*   Updated: 2023/11/20 16:20:17 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_equal_sign(char *str)
{
	if (*str == '=')
		return (0);
	while (*str && *str != '=')
		str++;
	if (!*str)
		return (1);
	if (*str == '=' && *(str + 1) && *(str + 1) != '=')
		return (1);
	if (*str == '=' && !*(str + 1))
		return (1);
	return (0);
}

static int	check_valid_string(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str && *str != '=')
	{
		if (is_varsep(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void	swap_strings(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	is_valid_arg(char *str)
{
	if (!check_equal_sign(str))
		return (0);
	if (!check_valid_string(str))
		return (0);
	return (1);
}