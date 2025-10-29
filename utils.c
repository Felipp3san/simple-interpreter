/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:54:32 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 19:04:19 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int	is_operator(t_intr *intr)
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
			return (1);
		i++;
	}
	return (0);
}
