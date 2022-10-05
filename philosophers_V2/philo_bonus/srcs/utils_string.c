/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:29:57 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/05 14:31:11 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_cnt(long long n)
{
	int	cnt;

	cnt = 1;
	if (n < 0)
	{
		n = -n;
		cnt++;
	}
	while (n >= 10)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_put(char *str, long long n, int len)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n >= 10)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	str[len] = n % 10 + 48;
	return (str);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;

	len = ft_cnt(n);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		exit(1);
	str[len] = 0;
	return (ft_put(str, n, len - 1));
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	int		s1_len;
	int		s2_len;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	temp = (char *)malloc(s1_len + s2_len + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (*s1 && s2)
		temp[i++] = *s1++;
	while (*s2 && s2)
		temp[i++] = *s2++;
	temp[i] = 0;
	return (temp);
}
