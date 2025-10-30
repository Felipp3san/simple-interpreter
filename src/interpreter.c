/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:32:42 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/30 01:25:31 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "lexer.h"
#include "token.h"
#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	Arithmetic expression parser / interpreter.

	calc>  14 + 2 * 3 - 6 / 2
	17

	expr	: term ((PLUS | MINUS) term)*
	term	: factor ((MUL | DIV) factor)*
	factor	: INTEGER
*/

void	error(void)
{
	printf("Error\n");
	exit (EXIT_FAILURE);
}

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
		error();
}

/*
	Return an INTEGER token value.

	factor : INTEGER | LPAREN expr RPAREN
*/
static int	factor(t_intr *intr)
{
	t_token	token;
	int		result;

	token = intr->current_token;
	if (token.type == LPAREN)
	{
		eat(intr, LPAREN);
		result = expr(intr);
		eat(intr, RPAREN);
		return (result);
	}
	else
	{
		eat(intr, INTEGER);
		return (token.value);
	}
}

/*
	term : factor((MUL | DIV) factor)*
*/
static int	term(t_intr	*intr)
{
	t_token	token;
	int		result;

	result = factor(intr);
	while (is_mul_div(intr->current_token.type))
	{
		token = intr->current_token;
		if (token.type == MUL)
		{
			eat(intr, MUL);
			result = result * factor(intr);
		}
		else if (token.type == DIV)
		{
			eat(intr, DIV);
			result = result / factor(intr);
		}
	}
	return (result);
}

/*
	expr : term ((MUL | DIV) term)*
*/
int	expr(t_intr *intr)
{
	t_token	token;
	int		result;

	result = term(intr);
	while (is_plus_minus(intr->current_token.type))
	{
		token = intr->current_token;
		if (token.type == PLUS)
		{
			eat(intr, PLUS);
			result = result + term(intr);
		}
		else if (token.type == MINUS)
		{
			eat(intr, MINUS);
			result = result - term(intr);
		}
	}
	return (result);
}

void	init_intr(t_intr *intr, t_lexer	*lexer)
{
	intr->lexer = lexer;
	intr->current_token = get_next_token(lexer);
}
