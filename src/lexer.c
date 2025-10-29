/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:22:26 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 20:47:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <ctype.h>
#include <string.h>

void	init_lexer(t_lexer *lex, char *str)
{
	lex->str = str;
	lex->pos = 0;
	lex->current_char = lex->str[0];
}

/*
	Advances current_char by one.
	If pos is greater than input len, set current_char as null.
*/
static void	advance(t_lexer *lex)
{
	lex->pos++;
	if (lex->pos > strlen(lex->str) - 1)
		lex->current_char = 0;
	else
		lex->current_char = lex->str[lex->pos];
}

/*
	Skips whitespaces before next token.
*/
static void	skip_spaces(t_lexer *lex)
{
	while (lex->current_char && isspace(lex->current_char))
		advance(lex);
}

/*
	Returns a multidigit integer consumed from the input.
*/
static int	integer(t_lexer *lex)
{
	int	result;

	result = 0;
	while (lex->current_char && isdigit(lex->current_char))
	{
		result = (result * 10) + (lex->current_char - '0');
		advance(lex);
	}
	return (result);
}

/*
	Lexical analyzer (also known as scanner or tokenizer)

	This method is responsible for breaking a sentence
	apart into tokens. One token at a time.
*/
t_token	get_next_token(t_lexer *lex)
{
	while (lex->current_char)
	{
		skip_spaces(lex);
		if (isdigit(lex->current_char))
			return ((t_token){integer(lex), INTEGER});
		else if (lex->current_char == '+')
		{
			advance(lex);
			return ((t_token){0, PLUS});
		}
		else if (lex->current_char == '-')
		{
			advance(lex);
			return ((t_token){0, MINUS});
		}
		else if (lex->current_char == '*')
		{
			advance(lex);
			return ((t_token){0, MULT});
		}
		else if (lex->current_char == '/')
		{
			advance(lex);
			return ((t_token){0, DIV});
		}
	}
	return ((t_token){0, EOF_TOK});
}
