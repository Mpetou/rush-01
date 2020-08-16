#include <unistd.h>
void ft_putchar(char c);
void rl();
void ps(char *str);
void psrl(char *str);
void pn(int n);
void pnrl(int n);
void pt(int *tab, int s);
void ptr(int *tab, int s);
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
//check left
int c_left(v2 coo, puzzle puz)
{
	//looking from left to right
	int h_b;
	int i;
	int v;
	int current_box;

	h_b = 0;
	i = -1;
	v = 0;
	while (i++ < 3)
	{
		current_box = puz.grid[i] [coo.y];
		if (h_b < current_box)
		{
			h_b = current_box;
			v++;
		}
	}
//	ps("pv left sees ");pnrl(v);
	return (v);
}
int c_right(v2 coo, puzzle puz)
{
	//looking from right to left
	int h_b;
	int i;
	int v;
	int current_box;

	h_b = 0;
	i = 4;
	v = 0;
	while (i-- > 0)
	{
		current_box = puz.grid[i] [coo.y];
		if (h_b < current_box)
		{
			h_b = current_box;
			v++;
		}
	}
//	ps("pv right sees ");pnrl(v);
	return (v);
}
int c_up(v2 coo, puzzle puz)
{
	//looking from top to bottom
	int h_b;
	int i;
	int v;
	int current_box;

	h_b = 0;
	i = -1;
	v = 0;
	while (i++ < 3)
	{
		current_box = puz.grid[coo.x] [i];
		if (h_b < current_box)
		{
			h_b = current_box;
			v++;
		}
	}
//	ps("pv up sees ");pnrl(v);
	return (v);
}
int c_down(v2 coo, puzzle puz)
{
	//looking from top to bottom
	int h_b;
	int i;
	int v;
	int current_box;

	h_b = 0;
	i = 4;
	v = 0;
	while (i-- > 0)
	{
		current_box = puz.grid[coo.x] [i];
		if (h_b < current_box)
		{
			h_b = current_box;
			v++;
		}
	}
//	ps("pv down sees ");pnrl(v);
	return (v);
}
