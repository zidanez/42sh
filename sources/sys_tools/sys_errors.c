/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <hgranule@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:37:58 by hgranule          #+#    #+#             */
/*   Updated: 2019/12/17 18:50:39 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_tools/sys_errors.h"
#include "sys_tools/sys_sh_configs.h"
#include "sys_tools/sys_tools.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "stdlib.h"
#include "dstring.h"
#include "env.h"
#include "bltn_math/math_hidden.h"

char		*g_errmess[ERR_CNT] =
{
	"",
	"Command not found",
	"Fork call failed",
	"Exec call failed",
	"Pipe call failed",
	"Permissions denied",
	"Redirection denied",
	"Bad file descriptor",
	"Memory allocation failed",
	"Is a directory",
	"Is not a regular file",
	"File creation failed",
	"File open failed, doesn't exist",
	"File open failed, permissions denied",
	"File open failed",
	"Is not a directory",
	"no such file or directory",
	"too many arguments",
	"invalid options",
	"cannot simultaneously unset a function and a variable",
	"unary operator expected",
	"binary operator expected",
	"integer expression expected"
};

char		*sys_get_std_message(int ecode)
{
	if (ecode > ERR_CNT)
		ecode = 0;
	return (g_errmess[ecode]);
}

void		sys_fatal_memerr(char *mess)
{
	char	buff[FATAL_BUFF_MSG_LEN];

	ft_bzero(buff, FATAL_BUFF_MSG_LEN);
	ft_strcpy(buff, SHELL_NAME_STD);
	ft_strcat(buff, ": Fatal error is occured: ");
	ft_strcat(buff, mess);
	ft_strcat(buff, "\n");
	ft_strcat(buff, "In this scope is, press any button to exit.");
	sys_error_message(buff, 0);
	sys_getch();
	exit(255);
}

int			sys_error_handler(char *descr, int ecode, ENV *envr)
{
	t_dyn_string	*message;

	if (!(message = dstr_new("")))
		sys_fatal_memerr("ERR_MESG_FAILED");
	if (descr)
	{
		dstr_insert_str(message, descr, MAX_LL);
		ecode ? dstr_insert_str(message, ": ", MAX_LL) : 0;
	}
	ecode ? dstr_insert_str(message, sys_get_std_message(ecode), MAX_LL) : 0;
	sys_perror(message->txt, -ecode, envr);
	dstr_del(&message);
	return (-ecode);
}

static char	*pull_err_token(ERR *err)
{
	char	*middle;
	char	*final;

	middle = " (error token is \"";
	final = ft_strjoin(middle, err->error_msg);
	middle = ft_strjoin(final, "\")");
	free(final);
	return (middle);
}

int			math_error_handler(ERR *err, int ret, ENV *env)
{
	char	*err_mess;
	char	*final_mess;
	char	*middle;

	final_mess = (err->err_code == VALUE_TOO_GREAT) ? MSG_ME_VLTG : NULL;
	final_mess = (err->err_code == INVALID_OP) ? MSG_ME_IVOP : final_mess;
	final_mess = (err->err_code == DOUBLE_COMPARE) ? MSG_ME_DCMP : final_mess;
	final_mess = (err->err_code == OPERAND_EXP) ? MSG_ME_OPEX : final_mess;
	final_mess = (err->err_code == INVALID_ASSIG) ? MSG_ME_IVAS : final_mess;
	final_mess = (err->err_code == STR_OPERAND) ? MSG_ME_STRO : final_mess;
	final_mess = (err->err_code == DIVISION_ZERO) ? MSG_ME_DVZR : final_mess;
	final_mess = (err->err_code == WEIRD_ERR) ? MSG_ME_WERR : final_mess;
	if (err->error_msg)
	{
		middle = pull_err_token(err);
		err_mess = ft_strjoin(final_mess, middle);
		free(middle);
	}
	else
		err_mess = ft_strdup(final_mess);
	sys_perror(err_mess, -1, env);
	free(err_mess);
	free(err->error_msg);
	return (ret);
}
