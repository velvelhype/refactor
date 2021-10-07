#include "ft.h"

extern	int	max_square_size;
extern	int max_square_col;
extern	int max_square_row;

int		map_colsize(char **map)
{
	int count = 0;

	while (map[1][count])
		count++;

	return (count);
}

void	init_square_scales(t_square_scales *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}

int		is_edge(char **map, int col, int row, t_init_map_info *map_status)
{
	if (col == map_colsize(map))
		return (FAIL);
	if (row == map_status->num_rows + 1)
		return (FAIL);
	if (map[row][col] == map_status->obstacle_char || map[row][col] == '\0')
		return (FAIL);

	return (SUCCESS);
}

int		ft_check_2(char **map, t_square_scales *latest_square, t_init_map_info *map_status)
{
	int offset;

	offset = 0;
	while (offset <= latest_square->size)
	{
		if (is_edge(map, latest_square->col + offset,
		latest_square->row + latest_square->size, map_status) == FAIL)
			return (FAIL);
		if (is_edge(map, latest_square->col + latest_square->size,
		latest_square->row + offset, map_status) == FAIL)
			return (FAIL);
		offset++;
	}
	return (SUCCESS);
}

void	detect_square_size(char **map, t_square_scales *latest_square, t_init_map_info *map_status)
{
	latest_square->size = 0;

	while (ft_check_2(map, latest_square, map_status) == SUCCESS)
		latest_square->size++;

	if (max_square_size < latest_square->size)
	{
		max_square_size	=	latest_square->size;
		max_square_col	=	latest_square->col;
		max_square_row	=	latest_square->row;
	}
}

void	draw_marked_map(char **map, t_init_map_info *map_status)
{
	int row = 1;
	int col;

	while (row <= map_status->num_rows)
	{
		col = 0;
		while (col < map_colsize(map))
		{
			write(1, &map[row][col], 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

char**	put_full_mark_on_map(char **map, t_init_map_info *map_status)
{
	int		row_offset;
	int		col_offset;

	row_offset = 0;
	while (row_offset < max_square_size)
	{
		col_offset = 0;
		while (col_offset < max_square_size)
		{
			map[max_square_row + row_offset][max_square_col + col_offset] = map_status->full_char;
			col_offset++;
		}
		row_offset++;
	}
	return	(map);
}

void	make_square(char **map, t_init_map_info *map_status)
{
	t_square_scales *latest_square = malloc(sizeof(t_square_scales));
	init_square_scales(latest_square);

	max_square_size = 0;
	max_square_col = 0;
	max_square_row = 0;

	while (latest_square->row <= map_status->num_rows)
	{
		latest_square->col = 0;
		while (latest_square->col < map_colsize(map))
		{
			if (is_edge(map, latest_square->col, latest_square->row, map_status))
				detect_square_size(map, latest_square, map_status);
			latest_square->col++;
		}
		latest_square->row++;
	}
	map = put_full_mark_on_map(map, map_status);
	draw_marked_map(map, map_status);
	free(latest_square);
}
