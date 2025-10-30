/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:53:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/30 00:43:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

# include "lexer.h"

typedef struct s_intr
{
	t_lexer	*lexer;
	t_token	current_token;
}	t_intr;

void	init_intr(t_intr *intr, t_lexer	*lexer);
int		expr(t_intr *intr);

#endif
