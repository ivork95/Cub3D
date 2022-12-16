/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 14:57:40 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/16 15:02:43 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtol.h"

static void	handle_endptr(t_stl_data *data, char **endptr, const char *nptr)
{
	if (endptr != 0)
	{
		if (data->any)
			*endptr = (char *) data->s - 1;
		else
			*endptr = (char *) nptr;
	}
}

static void	handle_neg(t_stl_data *data)
{
	if (data->acc < data->cutoff || (data->acc == data->cutoff
			&& data->c > data->cutlim))
	{
		data->any = -1;
		data->acc = LONG_MIN;
		errno = ERANGE;
	}
	else
	{
		data->any = 1;
		data->acc *= 10;
		data->acc -= data->c;
	}
}

static void	handle_pos(t_stl_data *data)
{
	if (data->acc > data->cutoff || (data->acc == data->cutoff
			&& data->c > data->cutlim))
	{
		data->any = -1;
		data->acc = LONG_MAX;
		errno = ERANGE;
	}
	else
	{
		data->any = 1;
		data->acc *= 10;
		data->acc += data->c;
	}
}

static void	set_cutoff_cutlim(t_stl_data *data)
{
	if (data->neg)
		data->cutoff = LONG_MIN;
	data->cutlim = data->cutoff % 10;
	data->cutoff /= 10;
	if (data->neg)
	{
		if (data->cutlim > 0)
		{
			data->cutlim -= 10;
			data->cutoff += 1;
		}
		data->cutlim = -data->cutlim;
	}
}

long	ft_strtol(const char *nptr, char **endptr)
{
	t_stl_data	data;

	init_stl_data(&data, nptr);
	while (isspace(*(data.s)))
		data.s++;
	if (*(data.s) == '-')
	{
		data.neg = 1;
		data.s++;
	}
	set_cutoff_cutlim(&data);
	while (isdigit((unsigned char) *(data.s)))
	{
		data.c = (unsigned char) *(data.s) - '0';
		data.s++;
		if (data.any < 0)
			continue ;
		if (data.neg)
			handle_neg(&data);
		else
			handle_pos(&data);
	}
	data.s++;
	handle_endptr(&data, endptr, nptr);
	return (data.acc);
}
