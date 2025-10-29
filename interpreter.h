/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:53:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 18:59:45 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

#define ERROR -1
#define SUCCESS 1

#include <stddef.h>

typedef enum e_type
{
	INTEGER,
	PLUS,
	MINUS,
	MULT,
	DIV,
	EOF_TOK
}	t_type;

typedef struct s_token
{
	int		value;
	t_type	type;
}	t_token;

typedef struct s_intr
{
	char	*str;
	char	current_char;
	size_t	pos;
	t_token	*current_token;
	void	(*error)(void);
}	t_intr;

t_token	*new_token(int value, t_type type);
void	advance(t_intr *intr);
void	skip_spaces(t_intr *intr);
int		is_operator(t_intr *intr);

#endif
