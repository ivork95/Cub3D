/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:07:42 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/01 12:22:27 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_strtol.h"

void	init_stl_data(t_stl_data *data, const char *nptr)
{
	data->s = nptr;
	data->neg = 0;
	data->cutoff = LONG_MAX;
	data->acc = 0;
	data->any = 0;
}
