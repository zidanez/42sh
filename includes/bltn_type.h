/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:36:07 by fnancy            #+#    #+#             */
/*   Updated: 2019/11/19 15:17:25 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLTN_TYPE_H
# define BLTN_TYPE_H

# include "bltn.h"

static char	*g_bltn_keywords[] = {"{", "}", "do",\
	"done", "else", "fi", "for", "function", "if", "in",\
	"then", "while"};

void	bltn_type_output(char *str, int type, DSTRING *val);
int		bltn_type_check_bins(char *str, ENV *env, DSTRING **val);
int		bltn_type_check_alias(char *str, DSTRING **val, ENV *env);
int		bltn_type_freespl(char ***spl);
void	bltn_type_freedstrings(t_darr *res);
char	**bltn_type_initspl(char ***spl, char *path);

#endif
