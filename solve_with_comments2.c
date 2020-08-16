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

int ft_how_much_does_a_pv_sees(vector st_p,int **grid)
{
	int highest_box;
	int viewed_boxes;
	int i;
	int current_box;
	vector dir;

	dir.x = (st_p.x == 0) - (st_p.x  == 3);
	dir.y = (st_p.y == 0) - (st_p.y  == 3);
	i = 0;
	highest_box = 0;
	viewed_boxes = 0;
	while (i < 4)
	{
		current_box = grid [st_p.x + dir.x * i]  [st_p.y + dir.y * i];
		if (current_box > highest_box)
		{
			viewed_boxes++;
			highest_box = current_box;
		}
		i++;
	}
	return (viewed_boxes);
}

int ft_can_put_box(vector pos, int box, puzzle puz)
{
	vector st_p;
	puz.grid [pos.x] [pos.y] = box;
	//up
	st_p.x = pos.x;
	st_p.y = 3;
	if (ft_how_much_does_a_pv_sees(st_p, puz.grid) > puz.pv_v[pos.x])
		return(1);
	//down
	st_p.x = pos.x;
	st_p.y = 0;
	if (ft_how_much_does_a_pv_sees(st_p, puz.grid) > puz.pv_v[pos.x + 4])
		return(2);
	//right
	st_p.x = 3;
	st_p.y = pos.y;
	if (ft_how_much_does_a_pv_sees(st_p, puz.grid) > puz.pv_h[pos.y + 4])
		return(3);
	//left
	st_p.x = 0;
	st_p.y = pos.y;
	if (ft_how_much_does_a_pv_sees(st_p, puz.grid) > puz.pv_h[pos.y])
		return(4);
	return (0);
}

int ft_put_box(puzzle puz, vector pos)
{	
	rl();
	rl();
	ft_print_grid(puz.grid);
	ps("trying to put box on case ");pn(pos.x);pnrl(pos.y);
	//eliminer des options les boxes deja pr2sentes
	int possible_boxes [4];
	char *errors [4] = 
	{
		"up",
		"down",
		"right",
		"left",
	};
	int i = 0;
	while (i < 4)
	{
		possible_boxes[i] = 0;
		possible_boxes[puz.grid [pos.x] [i]] = 1;
		possible_boxes[puz.grid [i] [pos.y]] = 1;
		i++;
	}
	ps("remaining possibilities: ");ptr(possible_boxes, 5);
	//try every remaining box
	i = 1;
	while (i < 5)
	{
		if (possible_boxes[i] == 0)
		{
			int can_put_result = ft_can_put_box(pos, i, puz);
			ps("trying to put ");pn(i);
			if (can_put_result == 0)
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
			{
				possible_boxes[i] = 1;
				ps(errors[can_put_result - 1]);
				psrl("... did not work -_-");
			}
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
