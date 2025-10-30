/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:48:08 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/30 00:44:42 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_lexer	lexer;
	t_intr	intr;
	int		result;

	if (argc == 1 || !*argv[1])
		return (EXIT_FAILURE);
	init_lexer(&lexer, argv[1]);
	init_intr(&intr, &lexer);
	result = expr(&intr);
	printf("Result: %d\n", result);
	return (EXIT_SUCCESS);
}
