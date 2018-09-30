/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 23:20:23 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/09/02 23:20:33 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <time.h>
# include <pthread.h>
# include <wchar.h>
# include <locale.h>
# include "libft/libft.h"

# define PNUM getpagesize()
# define N 1024
# define NCHUNK ((N * 1024 + PNUM - 1) / PNUM) * PNUM
# define M 8192
# define MCHUNK ((M * 256 + PNUM - 1) / PNUM) * PNUM
# define GETADDR(X) (void*)X+sizeof(t_block)

extern pthread_mutex_t g_mutex;

typedef struct	s_block{
	bool			start;
	bool			empty;
	unsigned int	size;
	void			*next;
}				t_block;

void			*malloc(size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();
t_block			*get_prev(t_block *ptr);
t_block			*find_ptr(void *ptr, int *type);
void			*find_empty_space(size_t size);
void			*ft_memcpy(void *restrict dst, const void *restrict src,
				size_t num);
void			*inner_malloc(size_t size, bool check_lock);
void			inner_free(void *ptr, bool check_lock);

extern void		*g_first[3];

#endif
