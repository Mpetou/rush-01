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
{pt(tab, s);rl();}

void set_tab (int **tab)
{
	int x = 0;
	int y = 0;
	while (y < 4)
	{
		while (x < 4)
		{
//			tab[x][y] = x + y *4;
			tab[x][y] = 0;
			x++;
		}
		y++;
		x = 0;
	}
}

typedef struct puzzle puzzle;
struct puzzle
{
	int **grid;
	int *pv_h;
	int *pv_v;
};

typedef struct v2 v2;
struct v2
{
	int x;
	int y;
};
void p_puz(puzzle puz)
{
	int x = 0;
	int y = 0;
	ps("   ");
	while (x < 4)
	{
		pn(puz.pv_v[x]);
		if (x != 3)
			ps("_");
		x++;
	}
	x = 0;
	rl();
	while (y < 4)
	{
		//afficher pv left
		pn(puz.pv_h[y]);ps("  ");
		while (x < 4)
		{
			pn(puz.grid[x][y]);
			if (x != 3)
				ps(" ");
			x++;
		}
		ps("  ");pn(puz.pv_h[y + 4]);
		rl();
		y++;
		x = 0;
	}
	x = 0;
	ps("   ");
	while (x < 4)
	{
		pn(puz.pv_v[x + 4]);
		if (x != 3)
			ps("_");
		x++;
	}
	rl();
}

v2 next_pos(v2 coo, puzzle puz)
{
	if (coo.x == 3)
	{
		coo.x = 0;
		coo.y++;
	}
	else
		coo.x++;
	if (puz.grid [coo.x] [coo.y] != 0)
	{
		if (coo.x == 3 && coo.y == 3)
			return (coo);
		else
			return next_pos(coo, puz);
	}
	return (coo);
}

int c_up(v2 coo, puzzle puz); 
int c_down(v2 coo, puzzle puz); 
int c_left(v2 coo, puzzle puz); 
int c_right(v2 coo, puzzle puz); 
//can put box
int can_p_b(v2 coo, int box, puzzle puz)
{
	puz.grid[coo.x][coo.y] = box;
	p_puz(puz);
//check if ANY eye sees too much---------------
//	ps("pv_u =");pnrl(puz.pv_v[coo.x]);
	if (c_up(coo, puz) > puz.pv_v[coo.x])
		return (1);

//	ps("pv_d =");pnrl(puz.pv_v[coo.x + 4]);
	if (c_down(coo, puz) > puz.pv_v[coo.x + 4])
		return (2);

//	ps("pv_l =");pnrl(puz.pv_h[coo.y]);
	if (c_left(coo, puz) > puz.pv_h[coo.y])
		return (3);

//	ps("pv_r =");pnrl(puz.pv_h[coo.y + 4]);
	if (c_right(coo, puz) > puz.pv_h[coo.y + 4])
		return (4);

	return (0);
}


//put box
int p_b(v2 coo, puzzle puz)
{
	ps("trying put box on case");pn(coo.x);pnrl(coo.y);
	if (coo.x == 3 && coo.y == 3 && puz.grid [3][3] != 0 )
	{
		psrl("fini!");
		return (1);
	}
//	p_puz(puz);
	char *errors [5] = 
	{
		"no errors",
		"up sees too much",
		"down sees too much",
		"left sees too much",
		"right sees too much"
	};
//setup ossibilities-----------------
	//ossible boxes
	int pos[5];
	int i;
	i = 0;
	while (i++ < 4)
		pos[i] = 1;
	i = -1;
	while (i++ < 3)
	{
		pos[puz.grid[coo.x][i]] = 0;
		pos[puz.grid[i][coo.y]] = 0;
	}
	ps("pos = "	);ptr(pos, 5);

	//try put box-------------------------
	i = 0;
	while (i++ < 4)
	{
		if (pos[i] == 1)
		{
			int r_can_p_b = can_p_b(coo, i, puz);
			ps("can_p_b returned ");psrl(errors[r_can_p_b]);
			if (r_can_p_b == 0)
			{
				if (coo.x == 3 && (c_left(coo, puz) < puz.pv_h[coo.y] || c_right(coo, puz) < puz.pv_h[coo.y + 4]))
				{
					psrl("one of the side pvs doesn't see enough");
					puz.grid[coo.x][coo.y] = 0;
					pos[i] = 0;
				}
				else if (coo.y == 3 && (c_up(coo, puz) < puz.pv_v[coo.x] || c_down(coo, puz) < puz.pv_v[coo.x + 4]))
				{
					ps("vertical pvs doesn't see enough up and down =");pn(c_up(coo, puz));pnrl(c_down(coo, puz));
					puz.grid[coo.x][coo.y] = 0;
					pos[i] = 0;
				}
				else
				{
					if (coo.x == 3 && coo.y == 3)
						return (1);
					if (p_b(next_pos(coo, puz), puz))
						return (1);
					else
					{
						puz.grid[coo.x][coo.y] = 0;
						pos[i] = 0;
						ps("previous p_b failed remaining pos=");ptr(pos, 5);//previous p_b failed
					}
				}
			}
			else
			{
				puz.grid[coo.x][coo.y] = 0;
				pos[i] = 0;
			}
		}
	}
	return (0);
}

int main (int argc, char **argv)
{
//setup puz-------------------------------
	puzzle puz;
	//setup grid
	int row0[4];
	int row1[4];
	int row2[4];
	int row3[4];
	int *grid[4];
	grid [0] = row0;
	grid [1] = row1;
	grid [2] = row2;
	grid [3] = row3;
	set_tab(grid);
	puz.grid = grid;

	//setup pvs
	(void)argc;
		int i;
	int pv_v [8];
	int pv_h [8];
	i = 0;
	while (i < 8)
	{
		pv_v [i] = argv[1] [i * 2] - '0';
		i++;
	}
	while (i < 16)
	{
		pv_h [i - 8]= argv[1] [i * 2] - '0';
		i++;
	}
	puz.pv_h = pv_h;
	puz.pv_v = pv_v;

	//show puz
//start solving puz--------------------------------
	v2 starting_coo;
	starting_coo.x = 0;
	starting_coo.y = 0;
	i = -1;
	while (i++ < 3)
	{
		if (pv_v[i] == 1)
			grid [i] [0] = 4;
		if (pv_h[i] == 1)
			grid [0] [i] = 4;
		if (pv_v[i + 4] == 1)
			grid [i] [3] = 4;
		if (pv_h[i + 4] == 1)
			grid [3] [i] = 4;
	}

	p_puz(puz);
	p_b(starting_coo, puz);
}
