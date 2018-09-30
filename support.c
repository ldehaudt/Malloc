/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 23:03:23 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 23:03:26 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*get_prev(t_block *ptr)
{
	t_block	*block;
	t_block	*prev;
	int		i;

	i = -1;
	while (++i < 3)
	{
		prev = NULL;
		block = (t_block*)g_first[i];
		while (block != NULL && block != ptr)
		{
			prev = block;
			block = block->next;
		}
		if (block != NULL)
			return (prev);
	}
	return (NULL);
}

t_block	*find_ptr(void *ptr, int *type)
{
	t_block	*block;
	int		i;

	if (!ptr)
	{
		return (NULL);
	}
	i = -1;
	while (++i < 3)
	{
		block = (t_block*)g_first[i];
		while (block != NULL && GETADDR(block) != ptr)
			block = block->next;
		if (block != NULL)
			break ;
	}
	if (i == 3)
	{
		return (NULL);
	}
	*type = i;
	return (block);
}

void	*find_empty_space(size_t size)
{
	t_block *tmp;

	if (size <= N)
		tmp = (t_block*)g_first[0];
	else if (size <= M)
		tmp = (t_block*)g_first[1];
	else
		tmp = (t_block*)g_first[2];
	while (tmp != NULL)
	{
		if (tmp->empty == 1)
		{
			if (tmp->size >= (unsigned int)size)
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t num)
{
	size_t		count;
	char		*p;
	const char	*p2;

	p = dst;
	p2 = src;
	count = 0;
	while (count < num)
	{
		p[count] = p2[count];
		count++;
	}
	return (dst);
}
