/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 20:23:51 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 20:23:53 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	merge_free(t_block **tmp, t_block **prev)
{
	t_block *next;
	t_block *bl;

	next = (*tmp)->next;
	(*tmp)->empty = 1;
	if ((*prev) && (*prev)->empty == 1)
	{
		(*prev)->size += (*tmp)->size;
		(*prev)->next = next;
		*tmp = *prev;
	}
	if (next && next->empty == 1 && next->start != 1)
	{
		(*tmp)->size += next->size;
		(*tmp)->next = next->next;
		bl = next->next;
	}
}

void	free_mem(int i, t_block **tmp, t_block **prev)
{
	if ((i == 0 && (*tmp)->size == (unsigned int)NCHUNK) ||
		(i == 1 && (*tmp)->size == (unsigned int)MCHUNK) || i == 2)
	{
		if ((*prev))
		{
			(*prev)->next = (*tmp)->next;
		}
		if (g_first[i] == *tmp)
		{
			g_first[i] = (*tmp)->next;
		}
		munmap(*tmp, (*tmp)->size);
	}
}

void	finish_free(t_block *tmp, t_block *prev, int i, bool check_lock)
{
	if (tmp != NULL)
	{
		merge_free(&tmp, &prev);
		prev = get_prev(tmp);
		free_mem(i, &tmp, &prev);
	}
	else
	{
		if (check_lock)
			pthread_mutex_unlock(&g_mutex);
		ft_putstr("freeing UNALLOCATED MEMORY\n");
	}
	if (check_lock)
		pthread_mutex_unlock(&g_mutex);
}

void	inner_free(void *ptr, bool check_lock)
{
	t_block	*tmp;
	t_block	*prev;
	int		i;

	prev = NULL;
	if (check_lock)
		pthread_mutex_lock(&g_mutex);
	if (!(tmp = find_ptr(ptr, &i)))
	{
		if (check_lock)
			pthread_mutex_unlock(&g_mutex);
		return ;
	}
	prev = get_prev(tmp);
	if (tmp->empty)
	{
		ft_putstr("freeing UNALLOCATED MEMORY\n");
		if (check_lock)
			pthread_mutex_unlock(&g_mutex);
		return ;
	}
	finish_free(tmp, prev, i, check_lock);
}

void	free(void *ptr)
{
	inner_free(ptr, true);
}
