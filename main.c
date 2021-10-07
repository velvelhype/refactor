#include "ft.h"

void	ft_free(char ***map)
{
	long int i;

	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}

char	*ft_read(int ifd)
{
	char	*content;
	char	buf[READ_SIZE + 1];
	int		n;

	content = NULL;
	while ((n = read(ifd, buf, READ_SIZE)) > 0)
	{
		buf[n] = '\0';
		if (content == NULL)
			content = ft_strdup(buf);
		else
			content = ft_strjoin(content, buf);
	}
	return (content);
}

int		for_stdio_map()
{
	char	*content;
	char	**map;
	t_map_info	*info;

	content = ft_read(0);
	if (is_end_newline(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	if (check_map_info(map) == FAIL)
		return (FAIL);
	if (!(info = parse_map_info(map)))
		return (FAIL);
	if (is_map_info_correct(map, info) == FAIL)
		return (FAIL);
	make_square(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		find_square(char *content)
{
	char	**map;
	t_map_info	*info;

	map = ft_split(content, "\n");
	free(content);
	if (check_map_info(map) == FAIL)
		return (FAIL);
	if (!(info = parse_map_info(map)))
		return (FAIL);
	if (is_map_info_correct(map, info) == FAIL)
		return (FAIL);
	make_square(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		for_arg_map(char *argv[], int i)
{
	int		ifd;
	char	*content;
	char	**map;
	t_map_info	*info;

	if ((ifd = open(argv[i], O_RDONLY)) == -1)
		return (FAIL);
	content = ft_read(ifd);
	close(ifd);
	if (is_end_newline(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	if (check_map_info(map) == FAIL)
		return (FAIL);
	if (!(info = parse_map_info(map)))
		return (FAIL);
	if (is_map_info_correct(map, info) == FAIL)
		return (FAIL);
	make_square(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		main(int argc, char *argv[])
{
	int i = 0;
	char *content;

	if (argc < 2)
	{
		content = ft_read(0);
		if (is_end_newline(content) == SUCCESS)
		{
			if (find_square(content) == FAIL)
				ft_putstr("map error\n");
		}
		else
		{
			ft_putstr("map error\n");
		}
	}
	else
	{
		while (++i < argc)
		{
			//コンテンツ読み込み
			//チェック
			if (for_arg_map(argv, i) == FAIL)
			ft_putstr("map error\n");
			if (!(i + 1 == argc))
				ft_putchar('\n');
		} 
	}
	return (0);
}
