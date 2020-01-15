/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaemoni <gdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:02:34 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/09/22 17:49:55 by gdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "sh_readline.h"
#include "sys_tools/sys_errors.h"

static void		ft_addstr(char **str1, const char *str2, t_concat *p, \
								const char *symbol)
{
	if (!str2)
		return ;
	ft_memcpy((*str1) + p->start, str2, p->size[p->n]);
	if (symbol[0] != '0')
		(*str1)[p->start++ + p->size[p->n]] = symbol[1];
	p->start = p->start + p->size[p->n];
}

size_t			*ft_errconcat(const size_t n)
{
	size_t		*rez;

	rez = (size_t*)malloc(sizeof(size_t) * (n + 1));
	if (rez == NULL)
		sys_fatal_memerr(sys_get_std_message(8));
	return (rez);
}

char			*ft_concat(const size_t n, const char *spec, ...)
{
	va_list			arg;
	t_concat		size;
	char			*tmp[n];
	char			*rez;

	ft_bzero(&size, sizeof(t_concat));
	size.size = ft_errconcat(n);
	va_start(arg, spec);
	while (++size.i < n + 1)
	{
		tmp[size.i] = va_arg(arg, char*);
		if (tmp[size.i])
			size.all += (size.size[size.i] = ft_strlen(tmp[size.i]));
		else
			size.size[size.i] = 0;
	}
	size.all += spec[0] != '0' ? n - 1 : 0;
	if (!(rez = (char*)malloc(sizeof(char) * size.all + 1)))
		return (NULL);
	while (++size.n < n + 1)
		ft_addstr(&rez, tmp[size.n], &size, spec);
	rez[size.start - ((spec[0] == '0') ? 0 : 1)] = '\0';
	free(size.size);
	va_end(arg);
	return (rez);
}

char			*ft_concatarr(const size_t n, const char *spec, \
							const char **arr)
{
	t_concat	size;
	char		*rez;

	ft_bzero(&size, sizeof(t_concat));
	if (!(size.size = (size_t*)malloc(sizeof(size_t) * n)))
		sys_fatal_memerr(sys_get_std_message(8));
	while (size.i < n)
	{
		if (arr[size.i])
			size.all += (size.size[size.i]) = ft_strlen(arr[size.i]);
		else
			size.size[size.i] = 0;
		++size.i;
	}
	if (spec[0] != '0')
		size.all += n - 1;
	if (!(rez = (char*)malloc(sizeof(char) * size.all + 1)))
		return (NULL);
	size.n = -1;
	while (++size.n < n + 1)
		ft_addstr(&rez, arr[size.n], &size, spec);
	rez[size.start - ((spec[0] == '0') ? 0 : 1)] = '\0';
	free(size.size);
	return (rez);
}
