#include "ft.h"

extern	int max_square_size;
extern	int max_square_col;
extern	int max_square_row;


int		is_edge(char **map, int col, int row, t_map_info *map_info)
{
	if (col == map_colsize(map))
		return (0);
	if (row == map_info->num_rows + 1)
		return (0);
	if (map[row][col] == map_info->obstacle || map[row][col] == '\0')
		return (0);
	return (1);
}

int		ft_check_2(char **map, t_map_sizes *bookmark_info, t_map_info *map_info)
{
	int i;

	i = 0;
	while (i <= bookmark_info->size)
	{
		if (is_edge(map, bookmark_info->col + i,
		bookmark_info->row + bookmark_info->size, map_info) == 0)
		{
			return (0);
		}
		i++;
	}
	i = 0;
	while (i <= bookmark_info->size)
	{
		if (is_edge(map, bookmark_info->col + bookmark_info->size,
		bookmark_info->row + i, map_info) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	detect_square_size(char **map, t_map_sizes *bookmark_info, t_map_info *map_info)
{
	bookmark_info->size = 0;
	while (ft_check_2(map, bookmark_info, map_info))
	{
		bookmark_info->size++;
	}
	if (max_square_size < bookmark_info->size)
	{
		max_square_size = bookmark_info->size;
		max_square_col = bookmark_info->col;
		max_square_row = bookmark_info->row;
	}
}

void	draw_marked_map(char **map, t_map_info *map_info)
{
	int i;
	int j;

	i = 1;
	while (i <= map_info->num_rows)
	{
		j = 0;
		while (j < map_colsize(map))
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

char**	put_x_mark_on_map(char **map, t_map_info *map_info)
{
	int		i;
	int		j;

	i = 0;
	while (i < max_square_size)
	{
		j = 0;
		while (j < max_square_size)
		{
			map[max_square_row + i][max_square_col + j] = map_info->x_mark;
			j++;
		}
		i++;
	}
	return	(map);
}

void	make_square(char **map, t_map_info *map_info)
{
	t_map_sizes *bookmark_info = malloc(sizeof(t_map_sizes));
	init_bookmark(bookmark_info);

	max_square_size = 0;
	max_square_col = 0;
	max_square_row = 0;

	while (bookmark_info->row <= map_info->num_rows)
	{
		bookmark_info->col = 0;
		while (bookmark_info->col < map_colsize(map))
		{
			if (is_edge(map, bookmark_info->col, bookmark_info->row, map_info))
				detect_square_size(map, bookmark_info, map_info);
			bookmark_info->col++;
		}
		bookmark_info->row++;
	}
	map = put_x_mark_on_map(map, map_info);
	draw_marked_map(map, map_info);
	free(bookmark_info);
}
