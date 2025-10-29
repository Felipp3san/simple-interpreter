/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:32:42 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 20:43:25 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	Compare if current_token type matches passed type.
	If yes, "eat" that token, freeing it then assign next token to current_token
	If not, free current_token and exits.
*/
static void	eat(t_intr *intr, t_type type)
{
	if (intr->current_token->type == type)
	{
		free(intr->current_token);
		intr->current_token = get_next_token(intr->lexer);
		if (!intr->current_token)
			intr->error();
	}
	else
	{
		free(intr->current_token);
		intr->current_token = NULL;
		intr->error();
	}
}

/*
	Validates if current_token type is operator.
*/
static int	is_operator(t_intr *intr)
{
	const t_type types[] = {
		PLUS,
		MINUS,
		MULT,
		DIV,
		EOF_TOK
	};
	int			i;
	
	i = 0;
	while (types[i] != EOF_TOK)
	{
		if (intr->current_token->type == types[i])
			return (true);
		i++;
	}
	return (false);
}

/*
	Return an INTEGER token value.

	factor : INTEGER
*/
static int	factor(t_intr *intr)
{
	int	value;

	value = intr->current_token->value;
	eat(intr, INTEGER);
	return (value);
}

/*
	Arithmetic expression parser / interpreter.

	expr	: factor ((MUL | DIV) factor)*
	factor	: INTEGER
*/
int	expr(t_intr *intr)
{
	t_token	*token;
	int		result;

	result = factor(intr);
	while (intr->current_token && is_operator(intr))
	{
		token = intr->current_token;
		if (token->type == PLUS)
		{
			eat(intr, PLUS);
			result = result + factor(intr);
		}
		else if (token->type == MINUS)
		{
			eat(intr, MINUS);
			result = result - factor(intr);
		}
		else if (token->type == MULT)
		{
			eat(intr, MULT);
			result = result * factor(intr);
		}
		else
		{
			eat(intr, DIV);
			result = result / factor(intr);
		}
	}
	if (intr->current_token)
	{
		free(intr->current_token);
		intr->current_token = NULL;
	}
	return (result);
}

void	error(void)
{
	printf("Error\n");
	exit (EXIT_FAILURE);
}

void	init_intr(t_intr *intr, t_lexer	*lexer)
{
	intr->lexer = lexer;
	intr->error = error;
	intr->current_token = get_next_token(lexer);
	if (!intr->current_token)
		intr->error();
}
