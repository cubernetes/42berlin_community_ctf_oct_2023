/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fferbuf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:28:11 by tosuman           #+#    #+#             */
/*   Updated: 2023/09/28 01:37:45 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50000
#endif

#ifndef EFLAG
# define EFLAG "@'eKkh*4kK0K=]=F1K[0K0>KSk0\\=j_\\r"
#endif

#define EFLAG_SIZE 34

typedef struct s_data
{
	char		username[BUFFER_SIZE];
	char		password[BUFFER_SIZE];
	char		flag[EFLAG_SIZE];
	int			divs[EFLAG_SIZE];
}				t_data;

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char	*o_dest;

	o_dest = dest;
	++n;
	while (--n && *src)
		*dest++ = *src++;
	while (n--)
		*dest++ = 0;
	return (o_dest);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}

void	ft_putnbr_fd(long nb, int fd)
{
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	else if (nb == INT_MIN)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(-(nb % 10), fd);
	}
	else if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-nb, fd);
	}
	else
		ft_putchar_fd(nb % 10 + '0', fd);
}

size_t	ft_strlen(char const *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

/* https://gist.github.com/sgsfak/9ba382a0049f6ee885f68621ae86079b */
unsigned int	djb33_hash(const char *s, size_t len)
{
	unsigned int	h;

	h = 5381;
	while (len--)
	{
		h += (h << 5);
		h ^= *s++;
	}
	return (h);
}

int	ft_pow(int a, int b)
{
	if (b == 0)
		return (1);
	while (--b)
		a *= a;
	return (a);
}

int	prime_count(int cap)
{
	unsigned int	n;
	int				pc;
	int				divisible;
	int				i;

	n = 1;
	pc = 0;
	while (++n <= cap)
	{
		if (n == 2 && ++pc)
			continue ;
		i = 1;
		divisible = 0;
		while (++i < n)
			if (n % i == 0 && ++divisible)
				break ;
		if (!divisible)
			++pc;
	}
	return (pc);
}

void	encrypt(const char *s, unsigned int key)
{
	int	pc;
	int	a;
	int	b;
	int	c;

	pc = prime_count(key);
	c = pc % 10;
	pc /= 10;
	b = pc % 10;
	pc /= 10;
	a = pc % 10;
	while (*s)
	{
		ft_putchar_fd((a * ft_pow(*s, 2) + b * ft_pow(*s, 1) + c) % 93 + 33, 1);
		ft_putstr_fd(", ", 1);
		ft_putnbr_fd((a * ft_pow(*s, 2) + b * ft_pow(*s, 1) + c) / 93, 1);
		ft_putstr_fd("\n", 1);
		++s;
	}
}

char	*decrypt(const char *s, unsigned int key, int *divs, int rot)
{
	double	inverse;
	double	p;
	double	q;
	int		pc;
	int		a;
	int		b;
	int		c;
	int		i;
	int		j;
	char	*buf;

	pc = prime_count(key + rot);
	c = pc % 10;
	pc /= 10;
	b = pc % 10;
	pc /= 10;
	a = pc % 10;
	p = ((double)b) / ((double)a);
	i = rot;
	while (i < 0)
		i += EFLAG_SIZE - 1;
	buf = malloc(sizeof(*buf) * (ft_strlen(s) + 1));
	j = 0;
	while (*s)
	{
		q = ((double)((double)c - (double)*s + 33.0 - 93.0 * (double)divs[i % (EFLAG_SIZE - 1)]))
			/ ((double)a);
		inverse = -p / 2.0 + sqrt(pow(p / 2.0, 2.0) - q);
		buf[j] = (char) inverse;
		++s;
		++i;
		++j;
	}
	buf[j] = 0;
	return (buf);
}

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	if (!n)
		return (0);
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 && *us2 && *us1 == *us2 && --n)
	{
		us1++;
		us2++;
	}
	if (*us1 != *us2)
		return ((*us1 - *us2 != 0) * (-2 * (*us1 - *us2 < 0) + 1));
	return (0);
}

int	main(int argc, char **argv)
{
	static t_data	data = {.flag = EFLAG, .divs = {177, 164, 637, 874, 676, 982,
			920, 198, 676, 587, 184, 874, 438, 786, 293, 815, 951, 587, 157, 184,
			587, 184, 151, 587, 889, 396, 184, 170, 293, 470, 844, 170, 1014}};
	unsigned int	hash_sum;
	char			*dpw;

	if (argc != 3)
	{
		ft_putstr_fd("[info] Usage: ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd(" USERNAME PASSWORD\n", 1);
		return (1);
	}
	if (ft_strlen(argv[1]) > sizeof(data.username) / sizeof(data.username[0]))
		return (ft_putstr_fd("[error] Username to long...\n", 2), 1);
	if (ft_strlen(argv[2]) > sizeof(data.password) / sizeof(data.password[0]))
		return (ft_putstr_fd("[error] Password to long...\n", 2), 2);
	ft_strncpy((char *)data.username, argv[1], sizeof(data.username)
		/ sizeof(data.username[0]));
	ft_strncpy((char *)data.password, argv[2], sizeof(data.password)
		/ sizeof(data.password[0]));
	ft_putstr_fd("[debug] Verifiying user \033[31m", 1);
	ft_putstr_fd((char *)data.username, 1);
	ft_putstr_fd("\033[m\n", 1);
	if (ft_strncmp(data.username, "monica", 7) && ft_strncmp(data.username,
			"bob", 7))
		return (ft_putstr_fd("[error] User does not exist!\n", 2), 3);
	ft_putstr_fd("[info] Decrypting data with user provided password (this might take a bit):\n",
		1);
	hash_sum = djb33_hash(data.username, ft_strlen(data.username))
		+ djb33_hash(data.password, ft_strlen(data.password));
	hash_sum %= 100000;
	/* ft_putstr_fd("Hash:\n", 1); */
	/* ft_putnbr_fd(hash_sum, 1); */
	/* ft_putstr_fd("\n", 1); */
	ft_putstr_fd("[debug] Transformed password:\n\033[32m", 1);
	dpw = decrypt(data.password, 77967 + BUFFER_SIZE, data.divs, -BUFFER_SIZE);
	ft_putstr_fd(dpw, 1);
	ft_putstr_fd("\033[m\n", 1);
	if (!ft_strncmp(dpw, "\x42\x54\x72\x33\x7c\x34\x32\x62\x74\x65\x7a\x77\x37\x66\x5f\x35\x74\x52\x6d\x42\x70\x79\x5e\x31\x35\x5f\x35\x2f\x5e\x75\x4d\x35\x33", 34))
	{
		free(dpw);
		ft_putstr_fd("[info] Decrypted data:\033[32m\n", 1);
		dpw = decrypt(data.flag, hash_sum, data.divs, 0);
		ft_putstr_fd(dpw, 1);
		ft_putstr_fd("\033[m\n", 1);
	}
	else
		ft_putstr_fd("[error] Password wrong!\n", 1);
	free(dpw);
	return (0);
}
