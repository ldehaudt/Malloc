/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 20:23:39 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 20:23:40 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	cont_main(char **str, int i)
{
	int size;

	while (++i < 100)
		if (!str[i])
		{
			size = rand() % (M - N - sizeof(t_block)) + N;
			str[i] = malloc(size);
			ft_memset(str[i], 'a', size);
		}
	while (++i < 150)
		if (!str[i])
		{
			size = rand() % (1242142 - sizeof(t_block)) + M;
			str[i] = malloc(size);
			ft_memset(str[i], 'a', size);
		}
	i = 0;
	while ((i += rand() % 3) < 150)
	{
		free(str[i]);
		str[i++] = NULL;
	}
	show_alloc_mem();
}

int		main(void)
{
	char	**str;
	int		size;
	int		i;

	str = malloc(150 * sizeof(char*));
	i = -1;
	while (++i < 150)
		str[i] = NULL;
	srand(time(NULL));
	while ((i = -1))
	{
		while (++i < 50)
			if (!str[i])
			{
				size = rand() % (N - 1 - sizeof(t_block)) + 1;
				str[i] = malloc(size);
				ft_memset(str[i], 'a', size);
			}
		cont_main(str, i);
	}
}
