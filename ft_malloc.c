/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 20:24:00 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 20:24:02 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*g_first[3] = {NULL, NULL, NULL};
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	add_malloc(void *addr, size_t size, void **ptr)
{
	t_block *b_full;
	t_block *b_empty;

	b_empty = NULL;
	b_full = (t_block*)addr;
	if (b_full->size - size >= sizeof(t_block))
	{
		b_empty = (t_block*)((void*)addr + size);
		b_empty->empty = 1;
		b_empty->start = 0;
		b_empty->next = b_full->next;
		b_empty->size = b_full->size - size;
	}
	b_full->empty = 0;
	b_full->size = size;
	b_full->next = (b_empty == NULL ? b_full->next : b_empty);
	*ptr = addr;
}

void	new_malloc_cont(size_t size, t_block *b_full, int alloc_size)
{
	t_block *b_empty;

	if (size <= M)
	{
		b_empty = (t_block*)((void*)b_full + size);
		b_full->next = b_empty;
		b_empty->next = (size <= N ? g_first[0] : g_first[1]);
		b_empty->size = alloc_size - size;
		b_empty->empty = 1;
		b_empty->start = 0;
	}
	else
	{
		b_full->next = g_first[2];
		if (g_first[2])
			b_empty = g_first[2];
	}
	if (size <= N)
		g_first[0] = b_full;
	else if (size <= M)
		g_first[1] = b_full;
	else
		g_first[2] = b_full;
}

void	new_malloc(size_t size, void **ptr)
{
	t_block	*b_full;
	int		alloc_size;

	alloc_size = 0;
	if (size <= N)
	{
		alloc_size = NCHUNK;
		*ptr = mmap(0, NCHUNK, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	else if (size <= M)
	{
		alloc_size = MCHUNK;
		*ptr = mmap(0, MCHUNK, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	}
	else
		*ptr = mmap(0, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	b_full = (t_block*)(*ptr);
	b_full->size = size;
	b_full->start = 1;
	b_full->empty = 0;
	new_malloc_cont(size, b_full, alloc_size);
}

void	*inner_malloc(size_t size, bool check_lock)
{
	void *addr;
	void *ptr;

	if (size == 0)
		return (NULL);
	if (check_lock)
		pthread_mutex_lock(&g_mutex);
	size += sizeof(t_block);
	if (size <= M && (addr = find_empty_space(size)) != NULL)
		add_malloc(addr, size, &ptr);
	else
		new_malloc(size, &ptr);
	if (check_lock)
		pthread_mutex_unlock(&g_mutex);
	return (ptr + sizeof(t_block));
}

void	*malloc(size_t size)
{
	return (inner_malloc(size, true));
}
