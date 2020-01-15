/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_func_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/11/22 16:01:21 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_req.h"
#include "sh_token.h"
#include "sh_tokenizer.h"

static char	*pull_return(char *str, t_dlist **tok, t_stx **tr)
{
	make_token(tok, NULL, RETURN);
	if (*(str + 6) == ' ' || *(str + 6) == '\t')
		make_token(tok, NULL, TK_EMPTY);
	str = skip_spaces(str + 6);
	if (!(*str))
		return (str);
	if (!(str = parse_str_block(str, tok, tr, '}')))
		return (NULL);
	expr_to_value(tok[1]);
	return (str);
}

static char	*func_args(char *str, t_dlist **tok, t_stx **tr)
{
	str++;
	str = skip_spaces_nd_nl(str);
	while (*str && *str != '}')
	{
		if (check_branch(str, tr[FLOWS]))
			str = block_pass(FLOWS, str, tok, tr);
		else if (check_branch(str, tr[ENVAR]))
			str = block_pass(ENVAR, str, tok, tr);
		else if (is_token_here(str, "return"))
			str = pull_return(str, tok, tr);
		else
			str = parse_comm(str, tok, tr, '}');
		if (!str)
			return (NULL);
		if (!sep_detected(tok[1]) || !check_valid_sep(tok[1]))
			return (NULL);
		str = skip_spaces_nd_nl(str);
	}
	if (!(*str))
		return (0);
	make_token(tok, NULL, TK_FEND);
	return (parse_sep(str + 1, tok, 0));
}

static char	*get_function(char *str, char *reg1, t_dlist **tok, t_stx **tr)
{
	size_t		i;
	char *const	reg2 = "{z}";

	str = skip_spaces(str);
	if ((*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122))
	{
		if ((i = layer_parse_two(reg1, str)))
		{
			i = (*(str + i - 1) == ')') ? i - 2 : i;
			make_token(tok, pull_token(str, i), TK_NAME);
			str += (*(str + i) == '(') ? i + 2 : i;
			str = parse_empty(str, reg1, tok);
			if ((layer_parse_two(reg2, str)))
				return (func_args(str, tok, tr));
			else
				return (NULL);
		}
	}
	return (NULL);
}

char		*parse_func(char *str, t_dlist **tok, t_stx **tree, short ind)
{
	char *const	patt0 = "function_";
	char *const	patt2 = "?()_";
	char		*tmp;

	ind = 0;
	str = parse_empty(str, 0x0, tok);
	if ((tmp = reg_process(patt0, TK_FUNCTION, str, tok)) != str && tmp)
		return (get_function(str + 8, "? ", tok, tree));
	else if ((layer_parse_two(patt2, str)))
	{
		make_token(tok, NULL, TK_FUNCTION);
		return (get_function(str, "!()", tok, tree));
	}
	return (NULL);
}

char		*parse_lambda(char *str, t_dlist **tok, t_stx **tree, short i)
{
	char *const reg2 = "{z}";

	str = parse_empty(str, 0x0, tok);
	if (*str != '{')
		str = parse_comm(str, tok, tree, 0);
	if (!(layer_parse_two(reg2, str)))
		return (NULL);
	make_token(tok, NULL, TK_LAMBDA);
	if (!(str = func_args(str, tok, tree)))
		return (NULL);
	return (parse_sep(str, tok, i));
}
