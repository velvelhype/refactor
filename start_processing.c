/*
====================================================
File overview
----------------------------------------------------
Loading given map, and give it to the function 
search the max drawble size square;
----------------------------------------------------
Index
----------------------------------------------------
free_map
read_and_malloc
parse_map_info
check_and_find_square
main
====================================================
*/

#include "ft.h"

void	free_map(char ***map)
{
	long int row;

	row = 0;
	while ((*map)[row])
	{
		free((*map)[row]);
		row++;
	}
	free(*map);
	*map = NULL;
}

char	*read_and_malloc(int ifd)
{
	char	*map_material;
	char	buf[READ_SIZE + 1];
	int		read_ret;

	map_material = NULL;
	while ((read_ret = read(ifd, buf, READ_SIZE)) > 0)
	{
		buf[read_ret] = '\0';
		if (map_material == NULL)
			map_material = ft_strdup(buf);
		else
			map_material = ft_strjoin(map_material, buf);
	}
	return (map_material);
}

t_initial_map_info	*parse_map_info(char **map)
{
	t_initial_map_info	*info;
	char	*line;
	int		len;
	int		i;
	char	*num;

	line = map[0];
	len = ft_strlen(line);
	info = malloc(sizeof(t_initial_map_info *));
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

int		check_and_find_square(char *map_material)
{
	char				**map;
	t_initial_map_info	*parsed_info;

	if (is_end_newline(map_material) == FAIL)
		return (FAIL);
	map = ft_split(map_material, "\n");
	if (valid_initial_map_info(map) == FAIL)
		return (FAIL);
	if (!(parsed_info = parse_map_info(map)))
		return (FAIL);
	if (is_init_and_parsed_info_same(map, parsed_info) == FAIL)
		return (FAIL);
	make_square(map, parsed_info);
	free_map(&map);
	free(parsed_info);
	return (SUCCESS);
}

int		main(int argc, char *argv[])
{
	int arg_offset = 0;
	int ifd;
	char *map_material;

	if (argc < 2)
	{
		map_material = read_and_malloc(0);
		if (check_and_find_square(map_material) == FAIL)
			ft_putstr("map error\n");
		free(map_material);
	}
	else
	{
		while (++arg_offset < argc)
		{
			if ((ifd = open(argv[arg_offset], O_RDONLY)) == -1)
				ft_putstr("map error\n");
			else
			{
				map_material = read_and_malloc(ifd);
				close(ifd);
				if (check_and_find_square(map_material) == FAIL)
					ft_putstr("map error\n");
				free(map_material);
			}
			if (!(arg_offset + 1 == argc))
				ft_putchar('\n');
		} 
	}
	return (0);
}
