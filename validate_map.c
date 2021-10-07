/*
====================================================
File overview 
----------------------------------------------------
functions validates map;
----------------------------------------------------
Index
----------------------------------------------------
is_t_info_correct
are_obstacle_and_empty_only
is_row_same
is_end_newline
valid_initial_map_info
is_init_and_parsed_info_same
====================================================
*/

#include "ft.h"

int		is_t_info_correct(char **map, t_initial_map_info *info)
{
	if (!(map[0] && map[1]))
		return (FAIL);
	if (!(	map[1][0] == info->empty_char ||
			map[1][0] == info->obstacle_char ||
			map[1][0] == info->full_char))
		return (FAIL);
	return (SUCCESS);
}

int		are_obstacle_and_empty_only(char **map, t_initial_map_info *info)
{
	int row;
	int col;

	row = 0;
	while (map[++row])
	{
		col = -1;
		while (map[row][++col])
		{
			if (!(map[row][col] == info->empty_char || map[row][col] == info->obstacle_char))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int		is_row_same(char **map, t_initial_map_info *info)
{
	int row;
	int len;

	row = 1;
	len = ft_strlen(map[row]);
	while (map[row])
	{
		if (len != ft_strlen(map[row]))
			return (FAIL);
		row++;
	}
	if (row - 1 != info->num_rows)
		return (FAIL);
	return (SUCCESS);
}

int		is_end_newline(char *content)
{
	int		grid;

	grid = 0;
	while (content[grid] != '\0')
		grid++;
	if (content[grid - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}

int		valid_initial_map_info(char **map)
{
	int		len;
	char	*initial_map_info;

	if (!map[0])
		return (FAIL);
	initial_map_info = map[0];
	len = ft_strlen(initial_map_info);
	if (len < 4)
		return (FAIL);
	int	i = -1;
	while (++i < len - 3)
		if (!(initial_map_info[i] >= '0' && initial_map_info[i] <= '9'))
			return (FAIL);
	if (!(is_printable(initial_map_info[len - 1]) &&
			is_printable(initial_map_info[len - 2]) &&
			is_printable(initial_map_info[len - 3])))
		return (FAIL);
	if (initial_map_info[len - 1] == initial_map_info[len - 2] ||
			initial_map_info[len - 2] == initial_map_info[len - 3] ||
			initial_map_info[len - 3] == initial_map_info[len - 1])
		return (FAIL);
	return (SUCCESS);
}

int		is_init_and_parsed_info_same(char **map, t_initial_map_info *info)
{
	if (is_t_info_correct(map, info) == FAIL
	|| are_obstacle_and_empty_only(map, info) == FAIL
	|| is_row_same(map, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
