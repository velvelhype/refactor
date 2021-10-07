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
	int		n;

	map_material = NULL;
	while ((n = read(ifd, buf, READ_SIZE)) > 0)
	{
		buf[n] = '\0';
		if (map_material == NULL)
			map_material = ft_strdup(buf);
		else
			map_material = ft_strjoin(map_material, buf);
	}
	return (map_material);
}

int		check_and_find_square(char *map_material)
{
	char	**map;
	t_init_map_info	*info;

	map = ft_split(map_material, "\n");
	if (check_initial_map_info(map) == FAIL)
		return (FAIL);
	if (!(info = parse_map_info(map)))
		return (FAIL);
	if (is_initial_map_info_correct(map, info) == FAIL)
		return (FAIL);
	make_square(map, info);
	free_map(&map);
	free(info);
	return (SUCCESS);
}

int		newline_check(char *map_material)
{
	if (is_end_newline(map_material) == SUCCESS)
		return (SUCCESS);
	else
		ft_putstr("map error\n");
	return (FAIL);
}

int		main(int argc, char *argv[])
{
	int i = 0;
	int ifd;
	char *map_material;

	if (argc < 2)
	{
		map_material = read_and_malloc(0);
		if(newline_check(map_material) == SUCCESS)
			if (check_and_find_square(map_material) == FAIL)
				ft_putstr("map error\n");
		free(map_material);
	}
	else
	{
		while (++i < argc)
		{
			if ((ifd = open(argv[i], O_RDONLY)) == -1)
				return (FAIL);
			map_material = read_and_malloc(ifd);
			close(ifd);
			if(newline_check(map_material) == SUCCESS)
				if (check_and_find_square(map_material) == FAIL)
					ft_putstr("map error\n");
			free(map_material);
			if (!(i + 1 == argc))
				ft_putchar('\n');
		} 
	}
	return (0);
}
