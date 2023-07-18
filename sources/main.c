/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesmart <mdesmart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:58:17 by mdesmart          #+#    #+#             */
/*   Updated: 2023/07/18 16:29:33 by mdesmart         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"


int main(int argc, char **argv)
{
	t_data data;

	if (!check_arg(argc, argv))
	{
		// printf("main1\n");
		if (!init_data(&data, argv))
		{
			// printf("main2\n");
			philo_launcher(&data);
		}
	}
	return (0);
}