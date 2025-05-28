/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:29:14 by tchampio          #+#    #+#             */
/*   Updated: 2025/05/12 10:08:41 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	get_taille(int n)
{
	int	t;

	t = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		t++;
	}
	return (t);
}

static char	*nb_pos(int i, int n)
{
	char	*str;

	str = malloc(sizeof(char) * get_taille(n) + 1);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

static char	*nb_neg(int i, int n)
{
	char	*str;

	str = malloc(sizeof(char) * get_taille(n) + 2);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i--;
	if (n == -2147483648)
	{
		str[i] = '8';
		i--;
		n = n / 10;
	}
	n *= -1;
	while (i >= 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n >= 0)
		str = nb_pos((get_taille(n)), n);
	else
		str = nb_neg((get_taille(n) + 1), n);
	return (str);
}
