/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:11:58 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/13 13:31:16 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	print_error(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

//if -60 warning "its not gonna work properly"
int	check_arg(int argc, char **argv)
{
	int i;
	int	j;

	i = 1;
	if (argc > 6 || argc < 5)
		return (print_error("wrong number of arguments\n"));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || argv[i][j] <= 0)
				return (print_error("one arg is not a valid number\n"));
			j++;
		}
		i++;
	}
	return (0);
}
