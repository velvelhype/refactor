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

void	set_zero_square_scales(t_square_scales *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}

int		is_grid_squareble(char **map, int col, int row, t_init_map_info *init_map_info)
{
	if (col == map_colsize(map))
		return (FAIL);
	if (row == init_map_info->num_rows + 1)
		return (FAIL);
	if (map[row][col] == init_map_info->obstacle_char || map[row][col] == '\0')
		return (FAIL);

	return (SUCCESS);
}

int		valid_square(char **map, t_square_scales *square, t_init_map_info *init_map_info)
{
	int offset;

	offset = 0;
	while (offset <= square->size)
	{
		if (is_grid_squareble(map, square->col + offset,
		square->row + square->size, init_map_info) == FAIL)
			return (FAIL);
		if (is_grid_squareble(map, square->col + square->size,
		square->row + offset, init_map_info) == FAIL)
			return (FAIL);
		offset++;
	}
	return (SUCCESS);
}

void	detect_square_size(char **map, t_square_scales *square, t_init_map_info *init_map_info)
{
	square->size = 0;

	while (valid_square(map, square, init_map_info) == SUCCESS)
		square->size++;

	if (max_square_size < square->size)
	{
		max_square_size	=	square->size;
		max_square_col	=	square->col;
		max_square_row	=	square->row;
	}
}

void	draw_marked_map(char **map, t_init_map_info *init_map_info)
{
	int row = 1;
	int col;

	while (row <= init_map_info->num_rows)
	{
		col = 0;
		while (col < map_colsize(map))
		{
			ft_putchar(map[row][col]);
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}

char**	put_full_mark_on_map(char **map, t_init_map_info *init_map_info)
{
	int		row_offset;
	int		col_offset;

	row_offset = 0;
	while (row_offset < max_square_size)
	{
		col_offset = 0;
		while (col_offset < max_square_size)
		{
			map[max_square_row + row_offset][max_square_col + col_offset] = init_map_info->full_char;
			col_offset++;
		}
		row_offset++;
	}
	return	(map);
}

void	make_square(char **map, t_init_map_info *init_map_info)
{
	t_square_scales *square = malloc(sizeof(t_square_scales));
	set_zero_square_scales(square);

	max_square_size = 0;
	max_square_col = 0;
	max_square_row = 0;

	while (square->row <= init_map_info->num_rows)
	{
		square->col = 0;
		while (square->col < map_colsize(map))
		{
			if (is_grid_squareble(map, square->col, square->row, init_map_info) == SUCCESS)
				detect_square_size(map, square, init_map_info);
			square->col++;
		}
		square->row++;
	}
	map = put_full_mark_on_map(map, init_map_info);
	draw_marked_map(map, init_map_info);
	free(square);
}
