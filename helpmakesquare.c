#include "ft.h"

extern	int max_square_size;
extern	int max_square_col;
extern	int max_square_row;

int		map_colsize(char **map)
{
	int count;

	count = 0;
	while (map[1][count])
	{
		count++;
	}
	return (count);
}

void	init_bookmark(t_map_sizes *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}