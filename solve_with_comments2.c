#include<stdio.h>
#include <unistd.h>

void ft_putchar(char c)
{write(1, &c, 1);}
void rl()
{ft_putchar('\n');}
void ps(char *str)
{
	int i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}
void psrl(char *str)
{ps(str);rl();}
void pn(int n)
{
	if (n >= 10)
	{
		pn(n / 10);
	}
	ft_putchar(n % 10 + '0');
}
void pnrl(int n)
{pn(n);rl();}
void pt(int *tab, int s)
{
	int i = 0;
	while (i < s)
	{
		pn(tab[i]);
		i++;
	}
}
void ptr(int *tab, int s)
{pt(tab, s); rl();}
void ft_print_grid(int **grid)
{
	int x = 0;
	int y = 0;
	while (x < 4)
	{
		while (y < 4)
		{
			pn(grid [x] [y]);
			if (y != 3)
				ft_putchar(' ');
			y++;
		}
	y = 0;
	ft_putchar('\n');
	x++;
	}
}

typedef struct puzzle puzzle;
struct puzzle
{
	int **grid;
	int *pv_h;
	int *pv_v;
};

typedef struct vector vector;
struct vector
{
	int x;
	int y;
};

vector ft_next_pos(vector pos)
{
	if(pos.x == 3)
	{
		pos.x = 0;
		pos.y ++;
	}
	else
		pos.x++;
	return (pos);
}

int ft_visibles_boxes(int *line)
{
	int visible_boxes;
	int highest_boxe;
	int index;

	visible_boxes = 0;
	highest_boxe = 0;
	index = 0;
	while (index < 4)
	{
		if (line[index] > highest_boxe)
		{
			highest_boxe = line[index];
			visible_boxes++;
		}
		index++;
	}
	return (visible_boxes);
}

int ft_can_put_box(vector	pos, int *box, puzzle puz)
{
	vector dir;
	int i;
	int j;
	int highest_box;
	int viewd_boxes;

	i = 0;
	highest_box = 0;
	viewd_boxes = 0;
	dir.x = 0;
	dir.y = 1;
	j = 0;
	while (j < 4)
	{
		while (1 < 4)
		{
			if (highest_boxe < puz.grid[dir.x * i] [dir.y * i])
			{
				viewd_boxes++;
				highest_boxe = 
}

int ft_put_box(puzzle puz, vector pos)
{	
	rl();
	rl();
	ft_print_grid(puz.grid);
	ps("trying to put box on case ");pn(pos.x);pnrl(pos.y);
	//eliminer des options les boxes deja pr2sentes
	int possible_boxes [5];
	int i = 0;
	possible_boxes [0] = 0;
	possible_boxes [1] = 1;
	possible_boxes [2] = 2;
	possible_boxes [3] = 3;
	possible_boxes [4] = 4;
	while (i < 4)
	{
		possible_boxes[puz.grid [pos.x] [i]] = 0;
		possible_boxes[puz.grid [i] [pos.y]] = 0;
		i++;
	}
	ps("remaining possibilities: ");ptr(possible_boxes, 5);
	//try every remaining box
	i = 1;
	while (i < 5)
	{
		if (possible_boxes[i] != 0)
		{
			ps("trying to put ");pn(possible_boxes[i]);
			if (ft_can_put_box(pos, possible_boxes + i, puz))
			{
				psrl("box has been putted");
				if (pos.x == 3 && pos.y == 3)
					return (1);
				if (ft_put_box(puz, ft_next_pos(pos)))
					return (1);
				else
				{
					puz.grid [pos.x] [pos.y] = 0;
					possible_boxes[i] = 0;
				}
			}
			else
				psrl("... did not work -_-");
		}
		i++;
	}
	return (0);
}


int ft_solve_grid (int **grid, int *pv_v, int *pv_h)
{
	psrl("called");
	puzzle puz;
	vector starting_pos;

	puz.pv_v = pv_v;
	puz.pv_h = pv_h;
	puz.grid = grid;
	rl();
	rl();
	rl();
	rl();
	ps("up points of view are: ");ptr(pv_v, 4);
	ps("down points of view are: ");ptr(pv_v + 4, 4);
	ps("left points of view are: ");ptr(pv_h, 4);
	ps("right points of view are: ");ptr(pv_h + 4, 4);

	starting_pos.x = 0;
	starting_pos.y = 0;
	if (ft_put_box(puz, starting_pos))
		{
			rl();
			psrl("puzzle solved");
			ft_print_grid(grid);
			return(1);
		}
		else
		{
			psrl("could not be solved");
			return(0);
		}
}
