/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 00:36:44 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/30 00:44:51 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdbool.h>

int	is_plus_minus(t_type type)
{
	return (type == PLUS || type == MINUS);
}

int	is_mul_div(t_type type)
{
	return (type == MUL || type == DIV);
}
