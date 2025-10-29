/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:48:08 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 19:07:44 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int		integer(t_intr *intr)
{
	int	result;

	result = 0;
	while (intr->current_char && isdigit(intr->current_char))
	{
		result = (result * 10) + (intr->current_char - '0');
		advance(intr);
	}
	return (result);
}

t_token	*get_next_token(t_intr *intr)
{
	while (intr->current_char)
	{
		skip_spaces(intr);
		if (isdigit(intr->current_char))
			return (new_token(integer(intr), INTEGER));
		else if (intr->current_char == '+')
		{
			advance(intr);
			return (new_token(0, PLUS));
		}
		else if (intr->current_char == '-')
		{
			advance(intr);
			return (new_token(0, MINUS));
		}
		else if (intr->current_char == '*')
		{
			advance(intr);
			return (new_token(0, MULT));
		}
		else if (intr->current_char == '/')
		{
			advance(intr);
			return (new_token(0, DIV));
		}
	}
	return (new_token(0, EOF_TOK));
}

void	eat(t_intr *intr, t_type type)
{
	if (intr->current_token->type == type)
	{
		free(intr->current_token);
		intr->current_token = get_next_token(intr);
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

int	term(t_intr *intr)
{
	int	value;

	value = intr->current_token->value;
	eat(intr, INTEGER);
	return (value);
}

int	expr(t_intr *intr)
{
	t_token	*token;
	int		result;

	intr->current_token = get_next_token(intr);
	if (!intr->current_token)
		intr->error();
	result = term(intr);
	while (intr->current_token && is_operator(intr))
	{
		token = intr->current_token;
		if (token->type == PLUS)
		{
			eat(intr, PLUS);
			result = result + term(intr);
		}
		else if (token->type == MINUS)
		{
			eat(intr, MINUS);
			result = result - term(intr);
		}
		else if (token->type == MULT)
		{
			eat(intr, MULT);
			result = result * term(intr);
		}
		else
		{
			eat(intr, DIV);
			result = result / term(intr);
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

void	init_intr(t_intr *intr, char **argv)
{
	memset(intr, 0, sizeof(t_intr));
	intr->str = argv[1];
	intr->current_char = intr->str[intr->pos];
	intr->error = error;
}

int	main(int argc, char **argv)
{
	t_intr	intr;
	int		result;

	if (argc == 1 || !*argv[1])
		return (0);
	init_intr(&intr, argv);
	result = expr(&intr);
	printf("Result: %d\n", result);
	return (EXIT_SUCCESS);
}

