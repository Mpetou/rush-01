/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabidal- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 18:24:33 by mabidal-          #+#    #+#             */
/*   Updated: 2020/08/15 19:25:33 by mabidal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putnum(int n)
{
	ft_putchar(n + '0');
}

void ft_print_gri(int **grid)
{
	int x = 0;
	int y = 0;
	while (x < 4)
	{
		while (y < 4)
		{
			grid [x] [y] = 0;
			ft_putnum(grid [x] [y]);
			if (y != 3)
				ft_putchar(' ');
			y++;
		}
	y = 0;
	ft_putchar('\n');
	x++;
	}
}

int main (int argc, char **argv)
{
	(void) argc;
	int i;
	int pv_verticaux [8];
	int pv_horizontaux [8];
	int row0 [4];
	int row2 [4];
	int row1 [4];
	int row3 [4];
	int *grid [4];

	//initialize points of views
	int x;
	int y;   
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

	//initialize grid
	x = 0;
	y = 0;
	grid [0] = row0;
	grid [1] = row1;
	grid [2] = row2;
	grid [3] = row3;
	while (x < 4)
	{
		while (y < 4)
		{
			grid [x] [y] = 0;
			y++;
		}
	y = 0;
	x++;
	}

	ft_print_gri(grid);
}
