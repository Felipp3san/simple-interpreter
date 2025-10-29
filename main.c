/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:48:08 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/26 23:48:05 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define ERROR -1
#define SUCCESS 1

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
	t_token	*left;
	t_token	*right;
	t_token	*op;
}	t_intr;

void	advance(t_intr *intr)
{
	intr->pos++;
	if (intr->pos > strlen(intr->str) - 1)
		intr->current_char = 0;
	else
		intr->current_char = intr->str[intr->pos];
}

void	skip_spaces(t_intr *intr)
{
	while (intr->current_char && isspace(intr->current_char))
		advance(intr);
}

t_token	*new_token(int value, t_type type)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

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

int	eat(t_intr *intr, t_type type)
{
	if (intr->current_token->type == type)
	{
		intr->current_token = get_next_token(intr);
		if (!intr->current_token)
			return (ERROR);
		return (SUCCESS);
	}
	intr->current_token = NULL;
	return (ERROR);
}

int	expr(t_intr *intr)
{
	intr->current_token = get_next_token(intr);
	if (!intr->current_token)
		return (ERROR);
	intr->left = intr->current_token;
	if (eat(intr, INTEGER) == ERROR)
		return (ERROR);
	intr->op = intr->current_token;
	if (intr->op->type == PLUS)
	{
		if (eat(intr, PLUS) == ERROR)
			return (ERROR);
	}
	else if (intr->op->type == MINUS)
	{
		if (eat(intr, MINUS) == ERROR)
			return (ERROR);
	}
	else if (intr->op->type == MULT)
	{
		if (eat(intr, MULT) == ERROR)
			return (ERROR);
	}
	else
	{
		if (eat(intr, DIV) == ERROR)
			return (ERROR);
	}
	intr->right = intr->current_token;
	if (eat(intr, INTEGER) == ERROR)
		return (ERROR);
	if (intr->op->type == PLUS)
		return (intr->left->value + intr->right->value);
	else if (intr->op->type == MINUS)
		return (intr->left->value - intr->right->value);
	else if (intr->op->type == MULT)
		return (intr->left->value * intr->right->value);
	else
		return (intr->left->value / intr->right->value);
}

void	free_all(t_intr *intr)
{
	if (intr->left)
	{
		free(intr->left);
		intr->left = NULL;
	}
	if (intr->op)
	{
		free(intr->op);
		intr->op = NULL;
	}
	if (intr->right)
	{
		free(intr->right);
		intr->right = NULL;
	}
	if (intr->current_token)
	{
		free(intr->current_token);
		intr->current_token = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_intr	intr;
	int		result;

	if (argc == 1 || !*argv[1])
		return (0);
	memset(&intr, 0, sizeof(t_intr));
	intr.str = argv[1];
	intr.current_char = intr.str[intr.pos];
	result = expr(&intr);
	if (result == ERROR)
		printf("Error\n");
	else
		printf("Result: %d\n", result);
	free_all(&intr);
	return (0);
}

