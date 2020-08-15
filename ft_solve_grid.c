struct puzzle
{
	int **grid;
	int *pv_h;
	int *pv_v;
}

struct position
{
	int x;
	int y;
}

position ft_next_pos(position pos)
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

int ft_visibles_boxes(int *line, int pv)
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


int ft_can_put_box(position	pos, int *box, puzzle puz)
{
	int test_line [4];
	int i;
	int pv;
	int unsitisfied_pvs;

	unsitisfied_pvs = 0;
	grid[pos.x] [pos.y] = *box;
	//up
	i = 0;
	while (i < 4)
	{
		test_line [i] = grid [pos.x] [i];
		i++;
	}
	pv = puzzle.pv_v[pos.x]; 
	unsitisfied_pvs += (ft_visibles_boxes(test_line, pv) > pv);

	//down
	i = 3;
	while (i >= 0)
	{
		test_line [i] = grid [pos.x] [i];
		i--;
	}
	pv = puzzle.pv_v[pos.x + 4];
	unsitisfied_pvs += (ft_visibles_boxes(test_line, pv) > pv);

	//left
	i = 0;
	while (i < 4)
	{
		test_line [i] = grid [i] [pos.y];
		i++;
	}
	pv = puzzle.pv_h[pos.y]; 
	unsitisfied_pvs += (ft_visibles_boxes(test_line, pv) > pv);
	
	//right
	i = 4;
	while (i >= 0)
	{
		test_line [i] = grid [i] [pos.y];
		i++;
	}
	pv = puzzle.pv_h[pos.y + 4]; 
	unsitisfied_pvs += (ft_visibles_boxes(test_line, pv) > pv);

	if (unsitisfied_pvs > 0)
	{
		puz.grid [pos.x] [pos.y] = 0;
		*box = 0;
		return (0);
	}
	else
		return(1);
}

int ft_put_box(puzzle puz, position pos)
{
	//eliminer des options les boxes deja pr2sentes
	int possible_boxes [5];
	int = 0;

	possible_boxes [0] = 0;
	possible_boxes [1] = 1;
	possible_boxes [2] = 2;
	possible_boxes [3] = 3;
	possible_boxes [4] = 4;
	i = 0;
	while (i < 5)
	{
		possible_boxes[grid [pos.x] [i]] = 0;
		possible_boxes[grid [i] [pos.y]] = 0;
		i++;
	}

	i = 0;
	while (i < 5)
	{
		if (possible_boxes[i] != 0)
		{
			if (ft_can_put_box(pos, (possible_boxes + i), puz)
			{
				if (pos.x == 0 && pos.y == 0)
					return (1);
				if (ft_put_box(puz, ft_next_pos(pos))
				{
					return (1);
				}
				else
				{
					grid [pos.x] [pos.y] = 0;
					possible_boxes[i] = 0;
				}
			}
		}
	}
	return (0);
}



int ft_solve_grid (int **grid, int *pv_v, int *pv_h)
{
	
}
