/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 22:33:57 by hgranule          #+#    #+#             */
/*   Updated: 2019/10/20 09:56:23 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

void	ft_putnbr(int nb)
{
	ft_putnbr_fd(nb, STDOUT_FILENO);
}
