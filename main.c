/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabidal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 18:24:33 by mabidal-          #+#    #+#             */
/*   Updated: 2020/08/16 18:34:39 by mabidal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
int ft_solve_grid ( int *pv_v, int *pv_h);
int main (int argc, char **argv)
{

	(void) argc;
	int i;
	int pv_verticaux [8];
	int pv_horizontaux [8];
	i = 0;
	while (i < 8)
	{
		pv_verticaux [i] = argv[1] [i * 2] - '0';
		i++;
	}
	while (i < 16)
	{
		pv_horizontaux [i - 8]= argv[1] [i * 2] - '0';
		i++;
	}
	ft_solve_grid( pv_verticaux, pv_horizontaux);
}
