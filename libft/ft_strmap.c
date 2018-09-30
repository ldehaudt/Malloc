/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:30:47 by cwu               #+#    #+#             */
/*   Updated: 2018/04/16 21:30:48 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *t;
	char *u;

	if (!s || !(t = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	u = t;
	while (s && *s)
		*u++ = f(*s++);
	*u = '\0';
	return (t);
}