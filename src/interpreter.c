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
#include "token.h"
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
	if (intr->current_token.type == type)
		intr->current_token = get_next_token(intr->lexer);
	else
		intr->error();
}

/*
	Validates if current_token type is operator.
*/
static int	is_operator(t_intr *intr)
{
	t_token	token;

	token = intr->current_token;
	return (token.type >= PLUS && token.type <= DIV);
}

/*
	Return an INTEGER token value.

	factor : INTEGER
*/
static int	factor(t_intr *intr)
{
	t_token	token;

	token = intr->current_token;
	eat(intr, INTEGER);
	return (token.value);
}

/*
	Arithmetic expression parser / interpreter.

	expr	: factor ((MUL | DIV) factor)*
	factor	: INTEGER
*/
int	expr(t_intr *intr)
{
	t_token	token;
	int		result;

	result = factor(intr);
	while (intr->current_token.type != EOF_TOK && is_operator(intr))
	{
		token = intr->current_token;
		if (token.type == PLUS)
		{
			eat(intr, PLUS);
			result = result + factor(intr);
		}
		else if (token.type == MINUS)
		{
			eat(intr, MINUS);
			result = result - factor(intr);
		}
		else if (token.type == MULT)
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
}
