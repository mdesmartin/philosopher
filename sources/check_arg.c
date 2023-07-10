/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:11:58 by mdesmart          #+#    #+#             */
/*   Updated: 2023/06/28 13:33:45 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	print_error(char *message)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

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
			if (!ft_isdigit(argv[i][j]))
				return (print_error("one arg is not a digit\n"));
			j++;
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

