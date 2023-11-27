/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:45 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/11/27 16:43:39 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "structs.h"

/*--------------expand.c--------------*/
int		expand(t_node *node, char **env);

/*------------exceptions.c------------*/

/*-----------expand_utils.c-----------*/
int		is_varsep(char c);
int		nonvarlen(char *str, int quote);
char	*get_nonvarstr(char *str, int *i, int *quote);
char	*get_varstr(char *str, int *i, char **env);

#endif
