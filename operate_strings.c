#include "ft.h"

int		is_printable(char c)
{
	if (c < 0x20 || c == 0x7f)
		return (0);
	return (1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*res;
	int		i;

	i = 0;
	while (src[i])
		i++;
	if (!(res = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(res = malloc(sizeof(char) * size)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

// ft_atoi

int	ft_isspace(char c)
{
	if (c == ' ' ||
		c == '\n' ||
		c == '\t' ||
		c == '\v' ||
		c == '\f' ||
		c == '\r')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_atoi(char *str)
{
	int res;
	int sign;
	int i;

	res = 0;
	sign = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (sign % 2 == 1)
		return (res * -1);
	else
		return (res);
}

// ft_split

int		g_word_index = 0;
int		g_start = 0;
int		g_end = 0;
int		g_state = 0;

int		ft_is_in_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_get_wc(char *str, char *charset)
{
	int wc;
	int state;

	wc = 0;
	state = OUT;
	while (*str)
	{
		if (ft_is_in_charset(*str, charset))
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			++wc;
		}
		++str;
	}
	return (wc);
}

void	ft_update_in_word(int i)
{
	if (g_state == OUT)
	{
		g_state = IN;
		g_start = i;
		g_end = i;
	}
	else
		g_end = i;
}

void	ft_add_last_word(char **res, char *str, int i)
{
	int j;

	if (g_state == IN)
	{
		res[g_word_index] = malloc(sizeof(char) * ((i - g_start) + 1));
		j = -1;
		while (g_start <= i)
			res[g_word_index][++j] = str[g_start++];
		res[g_word_index][++j] = '\0';
		g_word_index++;
	}
	res[g_word_index] = 0;
	g_word_index = 0;
	g_start = 0;
	g_end = 0;
	g_state = 0;
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	int		i;
	int		j;

	res = malloc(sizeof(char *) * (ft_get_wc(str, charset) + 1));
	i = -1;
	while (str[++i])
	{
		if (ft_is_in_charset(str[i], charset))
		{
			if (g_state == OUT)
				continue;
			g_state = OUT;
			res[g_word_index] = malloc(sizeof(char) * ((g_end - g_start) + 1));
			j = -1;
			while (g_start <= g_end)
				res[g_word_index][++j] = str[g_start++];
			res[g_word_index][++j] = '\0';
			g_word_index++;
		}
		else
			ft_update_in_word(i);
	}
	ft_add_last_word(res, str, i);
	return (res);
}