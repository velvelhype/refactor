#ifndef FT_H
# define FT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libgen.h>

# define READ_SIZE 320000
# define IN 1
# define OUT 0
# define SUCCESS 1
# define FAIL 0

typedef	struct	s_initial_map_info
{
	int		num_rows;
	char	empty_char;
	char	obstacle_char;
	char	full_char;
}				t_initial_map_info;

typedef	struct	s_square_scales
{
	int	col;
	int	row;
	int	size;
}				t_square_scales;

int					max_square_size;
int					max_square_col;
int					max_square_row;
void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
char				*ft_strdup(char *src);
char				*ft_strjoin(char *s1, char *s2);
char				**ft_split(char *str, char *charset);
int					ft_atoi(char *str);
int					is_printable(char c);
int					valid_initial_map_info(char **map);
t_initial_map_info	*parse_map_info(char **map);
int					is_init_and_parsed_info_same(char **map, t_initial_map_info *info);
int					is_end_newline(char *content);
void				set_zero_square_scales(t_square_scales *p_tempcrs);
int					is_grid_squareble(char **map, int col, int row, t_initial_map_info *p_info);
void				make_square(char **map, t_initial_map_info *p_info);
int					map_colsize(char **map);

#endif
