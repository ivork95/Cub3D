/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:05:10 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/16 14:47:47 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOL_H
# define FT_STRTOL_H

/* Private libraries */
# include "structs.h"

/* Public libraries */
# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <stdlib.h>

/* utils_ft_strtol.c */
void	init_stl_data(t_stl_data *data, const char *nptr);

/* ft_strtol.c */
long	ft_strtol(const char *nptr, char **endptr);

#endif