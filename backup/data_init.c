/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 21:33:11 by donglee           #+#    #+#             */
/*   Updated: 2020/04/09 21:33:29 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	data_init(t_data *data)
{
	data->flag[MINUS] = FALSE;
	data->flag[ZERO] = FALSE;
	data->precision = -1;
	data->type = '\0';
	data->width = 0;
	data->i = 0;
}
