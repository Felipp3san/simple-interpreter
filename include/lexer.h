/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:22:47 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 20:46:51 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>
#include "token.h"

typedef struct s_lexer
{
	char	*str;
	char	current_char;
	size_t	pos;
}	t_lexer;

void	init_lexer(t_lexer *lex, char *str);
t_token	*get_next_token(t_lexer *lex);

#endif
