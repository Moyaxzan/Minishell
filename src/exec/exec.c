/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:27:51 by elrichar          #+#    #+#             */
/*   Updated: 2024/01/05 12:34:11 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_command(t_data *data, t_node *node)
{
	if (expand(data, node, data->env->envtab))
		return (g_err_code);
	if (export_lastarg(data, node) == UNKNOWN_ERR)
		return (g_err_code);
	if (node->redirects)
		if (handle_redirections(data, node))
			return (g_err_code);
	if (node->arguments && node->arguments[0] && !srch_builtin(data, node))
		g_err_code = execute(data, node);
	if (data->tree && node->redirects)
		reset_rds(&(data->fds), node);
	return (g_err_code);
}

int	exec_or(t_data *data, t_node *tree)
{
	if (!handle_redirections(data, tree) && exec(data, tree->operand->l_child))
		exec(data, tree->operand->r_child);
	if (tree->redirects)
		reset_rds(&(data->fds), tree);
	return (g_err_code);
}

int	exec_and(t_data *data, t_node *tree)
{
	if (tree->redirects)
		if (handle_redirections(data, tree))
			return (g_err_code);
	if (!exec(data, tree->operand->l_child))
	{
		if (exec(data, tree->operand->r_child))
			return (g_err_code);
	}
	else
		return (g_err_code);
	if (tree->redirects)
		reset_rds(&(data->fds), tree);
	return (g_err_code);
}

int	exec_subshell(t_data *data, t_node *node)
{
	int	pid;
	int	childval;

	pid = 0;
	childval = 0;
	if (node->subshell)
		pid = fork();
	if (pid == -1)
		return (fatal_error(data, "fork"));
	if (!pid)
	{
		if (node->arguments || (!node->operand && node->redirects))
			g_err_code = exec_command(data, node);
		else if (node->operand->optype == T_OR)
			g_err_code = exec_or(data, node);
		else if (node->operand->optype == T_AND)
			g_err_code = exec_and(data, node);
		else if (node->operand->optype == T_PIPE)
			g_err_code = exec_pipe(data, node);
		exit_all(data, g_err_code);
	}
	else if (waitpid(pid, &childval, 0) == -1)
		exit_line(data, errnl(UNKNOWN_ERR, "minishell: waitpid failed"));
	return (WEXITSTATUS(childval));
}

int	exec(t_data *data, t_node *node)
{
	if (!node)
		return (g_err_code);
	if (node->subshell)
		g_err_code = exec_subshell(data, node);
	else if (!node->operand)
		g_err_code = exec_command(data, node);
	else
	{
		if (node->operand->optype == T_OR)
			g_err_code = exec_or(data, node);
		else if (node->operand->optype == T_AND)
			g_err_code = exec_and(data, node);
		else if (node->operand->optype == T_PIPE)
			g_err_code = exec_pipe(data, node);
	}
	return (g_err_code);
}
