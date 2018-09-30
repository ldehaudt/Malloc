/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 23:07:35 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 23:07:37 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	hex_digit(int num)
{
	if (num >= 0 && num < 10)
		return ('0' + num);
	else
		return ('a' + num - 10);
}

void	print_address_hex(void *ptr)
{
	int			i;
	uintptr_t	p;

	p = (uintptr_t)ptr;
	ft_putstr("0x");
	i = (sizeof(p) / 2 << 3) + 4;
	while ((i -= 4) >= 0)
		ft_putchar(hex_digit((p >> i) & 0xf));
}

int		show_alloc_ifs(t_block *bl, int i)
{
	if (bl->start)
	{
		if (i == 0)
			ft_putstr("TINY");
		if (i == 1)
			ft_putstr("SMALL");
		if (i == 2)
			ft_putstr("LARGE");
		ft_putstr(" : ");
		print_address_hex(bl);
		ft_putchar('\n');
	}
	if (bl->empty)
	{
		ft_putstr("Empty ✅  -> ");
		return (0);
	}
	else
	{
		ft_putstr("Full  ⛔  -> ");
		return (bl->size - sizeof(t_block));
	}
}

void	show_alloc_mem(void)
{
	t_block	*bl;
	int		total;
	int		i;

	setlocale(LC_ALL, "");
	pthread_mutex_lock(&g_mutex);
	total = 0;
	i = -1;
	while (++i < 3)
	{
		bl = g_first[i];
		while (bl)
		{
			total += show_alloc_ifs(bl, i);
			print_address_hex(GETADDR(bl));
			ft_putstr(" - ");
			print_address_hex((void*)bl + bl->size);
			ft_putstr(" : ");
			ft_putnbr(bl->size - sizeof(t_block));
			ft_putstr(" bytes\n");
			bl = bl->next;
		}
	}
	pthread_mutex_unlock(&g_mutex);
	printf("total : %d\n", total);
}
