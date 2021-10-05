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

typedef	struct	s_map_info
{
	int		num_rows;
	char	empty;
	char	obstacle;
	char	full;
}				t_map_info;

typedef	struct	s_tempcrs
{
	int	col;
	int	row;
	int	size;
}				t_tempcrs;

int				g_max;
int				g_col;
int				g_row;
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				ft_strlen(char *str);
int				ft_is_printable(char c);
char			*ft_strdup(char *src);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char *str, char *charset);
int				ft_atoi(char *str);
int				check_map_info(char **map);
t_map_info			*parse_map_info(char **map);
int				ft_validate(char **map, t_map_info *info);
int				is_end_newline(char *content);
void			set_crs(t_tempcrs *p_tempcrs);
int				ft_check_1(char **map, int col, int row, t_map_info *p_info);
void			make_square(char **map, t_map_info *p_info);
void			set_bsq(t_tempcrs *p_bsq);
int				ft_map_colsize(char **map);

#endif
