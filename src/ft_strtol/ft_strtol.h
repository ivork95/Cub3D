/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:05:10 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/11/29 15:14:43 by kgajadie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOL_H
# define FT_STRTOL_H

# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <stdlib.h>
# include "../structs.h"

/* utils_ft_strtol.c */
void	init_data(t_data *data, const char *nptr);

/* ft_strtol.c */
long	ft_strtol(const char *nptr, char **endptr);

#endif