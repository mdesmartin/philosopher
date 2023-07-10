/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:58:17 by mdesmart          #+#    #+#             */
/*   Updated: 2023/06/28 15:17:50 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"


int main(int argc, char **argv)
{
	t_data data;

	if (!check_arg(argc, argv))
	{
		init_structures(&data, argv);
		philo_launcher(&data);
	}
	return (0);
}