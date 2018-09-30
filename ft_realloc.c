/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 20:24:09 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 20:24:11 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	enact_realloc(t_block *block, size_t size, void **ptr)
{
	t_block	*next;
	t_block	*tmp;
	int		num;

	if (block->size < (unsigned int)size)
	{
		next = block->next;
		if (next && next->empty && next->size + block->size -
		sizeof(t_block) >= size)
		{
			block->size = size;
			tmp = (t_block*)((void*)block + size);
			num = next->size;
			block->next = tmp;
			tmp->next = next->next;
			tmp->empty = 1;
			tmp->size = num - size + sizeof(t_block);
		}
		else
		{
			*ptr = inner_malloc(size, false);
			ft_memcpy(*ptr, GETADDR(block), block->size - sizeof(t_block));
			inner_free(GETADDR(block), false);
		}
	}
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	int		i;

	size += sizeof(t_block);
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	if (!(block = find_ptr(ptr, &i)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (block != NULL)
	{
		enact_realloc(block, size, &ptr);
	}
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
