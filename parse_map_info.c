#include "ft.h"

t_init_map_info	*parse_map_info(char **map)
{
	t_init_map_info	*info;
	char	*line;
	int		len;
	int		i;
	char	*num;

	line = map[0];
	len = ft_strlen(line);
	info = malloc(sizeof(t_init_map_info *));
	num = malloc(sizeof(char) * (len - 3) + 1);
	i = -1;
	while (++i < len - 3)
		num[i] = line[i];
	num[i] = '\0';
	info->num_rows = ft_atoi(num);
	info->empty_char = line[len - 3];
	info->obstacle_char = line[len - 2];
	info->full_char = line[len - 1];
	free(num);

	return (info);
}
