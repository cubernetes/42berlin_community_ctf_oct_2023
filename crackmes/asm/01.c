/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <timo42@proton.me>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:17:53 by tischmid          #+#    #+#             */
/*   Updated: 2023/09/28 01:20:48 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define OPEN_MAX 4096
#define BUFFER_SIZE 42

typedef struct s_all
{
	char	*prv[OPEN_MAX];
	char	*buf;
	ssize_t	bread;
	int		i;
	int		j;
	int		len;
}			t_gnl_vars;

char	*get_next_line(int fd)
{
	static t_gnl_vars	x;

	while (x.prv[fd] && x.prv[fd][x.len])
		++x.len;
	x.buf = malloc(x.len + BUFFER_SIZE + 1);
	x.bread = read(fd, x.buf + x.len, BUFFER_SIZE);
	if (x.bread < 0)
		return (free(x.buf), free(x.prv[fd]), x.len = 0, x.prv[fd] = NULL);
	(free(NULL), x.buf[x.len + x.bread] = 0, x.i = x.len, x.j = -1);
	while (--x.len >= 0)
		x.buf[x.len] = x.prv[fd][x.len];
	while (x.buf[++x.len] && x.buf[x.len] != '\n')
		;
	if (!x.buf[x.len] && x.bread == 0 && (free(x.buf), 1))
		return (x.buf = x.prv[fd], x.prv[fd] = NULL, x.len = 0, x.buf);
	if (!x.buf[x.len] && x.bread == BUFFER_SIZE && (free(x.prv[fd]), 1))
		return (x.prv[fd] = x.buf, x.len = 0, get_next_line(fd));
	if (!x.buf[x.len] || (x.buf[x.len] == '\n' && !x.buf[x.len + 1]))
		return (free(x.prv[fd]), x.prv[fd] = NULL, x.len = 0, x.buf);
	(free(x.prv[fd]), x.prv[fd] = malloc(sizeof(char) * (x.i + x.bread + 1)));
	if (!x.prv[fd])
		return (free(x.buf), free(x.prv[fd]), x.len = 0, x.prv[fd] = NULL);
	while (x.buf[x.len + 1 + ++x.j])
		x.prv[fd][x.j] = x.buf[x.len + 1 + x.j];
	return (x.prv[fd][x.j] = 0, x.buf[x.len + 1] = 0, x.len = 0, x.buf);
}

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	if (!n)
		return (0);
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	while (*us1 && *us2 && *us1 == *us2 && --n)
	{
		us1++;
		us2++;
	}
	if (*us1 != *us2)
		return ((*us1 - *us2 != 0)
			* (-2 * (*us1 - *us2 < 0) + 1));
	return (0);
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}


int	validate_flag(const char *flag)
{
	char	real_flag[58];

	real_flag[0] = '4';
	real_flag[1] = '2';
	real_flag[2] = 'c';
	real_flag[3] = 't';
	real_flag[4] = 'f';
	real_flag[5] = '{';
	real_flag[6] = '3';
	real_flag[7] = 'v';
	real_flag[8] = '3';
	real_flag[9] = '5';
	real_flag[10] = 'y';
	real_flag[11] = 't';
	real_flag[12] = 'h';
	real_flag[13] = 'i';
	real_flag[14] = 'n';
	real_flag[15] = 'g';
	real_flag[16] = '_';
	real_flag[17] = 'i';
	real_flag[18] = 's';
	real_flag[19] = '_';
	real_flag[20] = '0';
	real_flag[21] = 'p';
	real_flag[22] = '3';
	real_flag[23] = 'n';
	real_flag[24] = 's';
	real_flag[25] = '0';
	real_flag[26] = 'u';
	real_flag[27] = '5';
	real_flag[28] = 'c';
	real_flag[29] = '3';
	real_flag[30] = '_';
	real_flag[31] = 'i';
	real_flag[32] = 'f';
	real_flag[33] = '_';
	real_flag[34] = 'y';
	real_flag[35] = '0';
	real_flag[36] = 'u';
	real_flag[37] = '_';
	real_flag[38] = 'c';
	real_flag[39] = '4';
	real_flag[40] = 'n';
	real_flag[41] = '_';
	real_flag[42] = '5';
	real_flag[43] = '3';
	real_flag[44] = '4';
	real_flag[45] = 'd';
	real_flag[46] = '_';
	real_flag[47] = 'a';
	real_flag[48] = 's';
	real_flag[49] = 's';
	real_flag[50] = 'e';
	real_flag[51] = 'm';
	real_flag[52] = 'b';
	real_flag[53] = 'l';
	real_flag[54] = 'y';
	real_flag[55] = '}';
	real_flag[56] = '\n';
	real_flag[57] = '0';
	return (!ft_strncmp(flag, real_flag, 57));
}

int	main(void)
{
	char	*flag;

	ft_putstr("Enter the flag:");
	flag = get_next_line(0);
	if (validate_flag(flag))
		return (ft_putstr("That is correct! Wohoo!\n"), 0);
	else
		return (ft_putstr("Nope, try again, kiddooo.\n"), 1);
}
