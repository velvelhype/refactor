#include "ft.h"

int		is_t_info_ok(char **map, t_map_info *info)
{
	if (!(map[0] && map[1]))
		return (FAIL);
	if (!(map[1][0] == info->empty ||
			map[1][0] == info->obstacle ||
			map[1][0] == info->full))
		return (FAIL);
	return (SUCCESS);
}

int		are_obstacle_and_empty_ok(char **map, t_map_info *info)
{
	int i;
	int j;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!(map[i][j] == info->empty || map[i][j] == info->obstacle))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

int		is_row_same(char **map, t_map_info *info)
{
	int i;
	int len;

	i = 1;
	len = ft_strlen(map[i]);
	while (map[i])
	{
		if (len != ft_strlen(map[i]))
			return (FAIL);
		i++;
	}
	if (i - 1 != info->num_rows)
		return (FAIL);
	return (SUCCESS);
}

int		is_end_newline(char *content)
{
	int		i;

	i = 0;
	while (content[i] != '\0')
		i++;
	if (content[i - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}

int		check_map_info(char **map)
{
	int		len;
	char	*line;

	if (!map[0])
		return (FAIL);
	line = map[0];
	len = ft_strlen(line);
	if (len < 4)
		return (FAIL);
	int	i = -1;
	while (++i < len - 3)
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (FAIL);
	if (!(is_printable(line[len - 1]) &&
				is_printable(line[len - 2]) &&
				is_printable(line[len - 3])))
		return (FAIL);
	if (line[len - 1] == line[len - 2] ||
			line[len - 2] == line[len - 3] ||
			line[len - 3] == line[len - 1])
		return (FAIL);
	return (SUCCESS);
}

int		is_map_info_correct(char **map, t_map_info *info)
{
	if (is_t_info_ok(map, info) == FAIL
	|| are_obstacle_and_empty_ok(map, info) == FAIL
	|| is_row_same(map, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
