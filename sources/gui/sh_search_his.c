/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_search_his.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <hgranule@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:29:17 by gdaemoni          #+#    #+#             */
/*   Updated: 2019/12/01 16:14:02 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_readline.h"
#include "sh_termcomand.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

void		bakspace_dstr(DSTRING **str_srch)
{
	if ((*str_srch)->strlen)
	{
		(*str_srch)->strlen--;
		(*str_srch)->txt[(*str_srch)->strlen] = '\0';
	}
}

void		get_overlap_histr(t_darr *overlap, DSTRING *str_srch)
{
	size_t	c;
	size_t	j;

	c = S_DARR_STRINGS - g_histr.count - 1;
	j = (size_t)-1;
	ft_bzero(overlap, sizeof(t_darr));
	while (++c < S_DARR_STRINGS)
	{
		if (g_histr.strings[c]->txt && \
		dstr_search_dstr(g_histr.strings[c], str_srch, 0) != SIZE_T_MAX)
		{
			overlap->strings[++j] = g_histr.strings[c];
			if ((ssize_t)overlap->maxlen < g_histr.strings[c]->strlen)
				overlap->maxlen = g_histr.strings[c]->strlen;
			overlap->allsize += g_histr.strings[c]->strlen;
			overlap->count++;
		}
	}
}

t_indch		supplement_srch(DSTRING *str_srch, DSTRING **str_over, \
							t_indch indch)
{
	t_darr		overlap;
	size_t		i;

	i = -1;
	if ((*str_over) != NULL)
		*str_over = NULL;
	if (indch.ch == TAB)
		get_overlap_histr(&overlap, str_srch);
	while (indch.ch == TAB && overlap.count)
	{
		if (++i == overlap.count)
			i = 0;
		(*str_over) = overlap.strings[i];
		print_his_line(str_srch, (*str_over));
		indch.ch = ft_getch();
	}
	if (indch.ch == ESC)
		skip_escp();
	return (indch);
}

t_indch		control_histr(DSTRING **str_srch, DSTRING **str_over, t_indch indch)
{
	indch.ch = ft_getch();
	if (ft_isalpha(indch.ch) || indch.ch == ' ' || ft_isalnum(indch.ch))
		dstr_insert_ch((*str_srch), indch.ch, (*str_srch)->strlen);
	else if (indch.ch == BAKSP)
		bakspace_dstr(str_srch);
	if (indch.ch == ESC)
		skip_escp();
	if ((indch.ch != ' ' && !ft_isalpha(indch.ch) && indch.ch != 11 && \
		indch.ch != 12) && indch.ch != TAB && indch.ch != BAKSP && \
		!(indch.fl = 0) && !ft_isalnum(indch.ch))
		indch.ch = 0;
	indch = supplement_srch((*str_srch), str_over, indch);
	return (indch);
}

t_indch		sh_search_his(DSTRING **buf, t_indch indch)
{
	DSTRING			*str_srch;
	DSTRING			*str_over;

	str_srch = dstr_nerr("");
	str_over = NULL;
	indch.ch = 1;
	indch.fl = 0;
	while (indch.ch && indch.ch != 4)
	{
		print_his_line(str_srch, str_over);
		indch = control_histr(&str_srch, &str_over, indch);
		if ((indch.ch != ' ' && !ft_isalpha(indch.ch) && indch.ch != 11 && \
			indch.ch != 12) && indch.ch != TAB && indch.ch != BAKSP && \
			!(indch.fl = 0) && !ft_isalnum(indch.ch))
			indch.ch = 0;
	}
	if (str_over && str_over->strlen)
	{
		dstr_del(buf);
		(*buf) = dstr_nerr(str_over->txt);
	}
	dstr_del(&str_srch);
	indch.ind = (*buf)->strlen;
	return (indch);
}
