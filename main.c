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
	size_t	pos;
	t_token	*current_token;
	t_token	*left;
	t_token	*right;
	t_token	*op;
}	t_intr;

void	skip_spaces(t_intr *intr)
{
	while (intr->str[intr->pos] && isspace(intr->str[intr->pos]))
		intr->pos++;
}

t_token	*get_next_token(t_intr *intr)
{
	t_token	*token;
	char	current_char;
	int		value;

	skip_spaces(intr);
	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (intr->pos > strlen(intr->str) - 1)
	{
		token->value = 0;
		token->type = EOF_TOK;
		return (token);
	}
	current_char = intr->str[intr->pos];
	if (isdigit(current_char))
	{
		value = 0;
		while (isdigit(intr->str[intr->pos]))
			value = (value * 10) + intr->str[intr->pos++] - '0';
		token->value = value;
		token->type = INTEGER;
		return (token);
	}
	else if (current_char == '+')
	{
		token->value = 0;
		token->type = PLUS;
		intr->pos++;
		return (token);
	}
	else if (current_char == '-')
	{
		token->value = 0;
		token->type = MINUS;
		intr->pos++;
		return (token);
	}
	free(token);
	return (NULL);
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
	else
	{
		if (eat(intr, MINUS) == ERROR)
			return (ERROR);
	}
	intr->right = intr->current_token;
	if (eat(intr, INTEGER) == ERROR)
		return (ERROR);
	if (intr->op->type == PLUS)
		return (intr->left->value + intr->right->value);
	else
		return (intr->left->value - intr->right->value);
}

void	free_all(t_intr *intr)
{
	if (intr->left)
	{
		free(intr->left);
		intr->left = NULL;
	}
		free(intr->left);
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
	result = expr(&intr);
	if (result == ERROR)
		printf("Error\n");
	else
		printf("Result: %d\n", result);
	free_all(&intr);
	return (0);
}

