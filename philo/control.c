/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:33:03 by btanir            #+#    #+#             */
/*   Updated: 2024/08/11 09:56:59 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_control(int argc, char **argv)
{
	int	i;
	int	j;

	if ((argc < 5 || argc > 6) && printf("%s\n", ARGS_ERR))
		return (1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]) && printf("%s\n", ARGS_ERR))
				return (1);
	}
	return (0);
}
