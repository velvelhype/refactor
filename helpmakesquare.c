#include "ft.h"

extern	int g_max;
extern	int g_col;
extern	int g_row;

int		ft_map_colsize(char **map)
{
	int count;

	count = 0;
	while (map[1][count])
	{
		count++;
	}
	return (count);
}

void	set_crs(t_tempcrs *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}

int		ft_check_1(char **map, int col, int row, t_map_info *p_info)
{
	if (col == ft_map_colsize(map))
	{
		return (0);
	}
	if (row == p_info->num_rows + 1)
	{
		return (0);
	}
	if (map[row][col] == p_info->obstacle || map[row][col] == '\0')
	{
		return (0);
	}
	return (1);
}
