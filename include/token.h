/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:45:24 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/29 20:46:03 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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

t_token	*new_token(int value, t_type type);

#endif
