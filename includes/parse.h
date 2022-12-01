/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 10:58:14 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/01 12:24:37 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/* Public libraries */
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>

/* Private libraries */
# include "../libft/libft.h"
# include "tokenize.h"
# include "structs.h"
# include "ft_strtol.h"
# include "validate_tokens.h"

/* ll_to_a_map/c */
int		get_map_size(t_map_element *map_element);
int		get_map_col_size(t_map_element *map_element);
char	**ll_to_a_map(t_map_element *map_element);

/* parse.c */
int		strip_spaces(char *s);
t_rgb	build_rgb(char *str);
t_rgb	parse_floor_ceiling(t_map_element *map_element, int sub_type);
char	**parse_cordinal(t_map_element *map_element, int sub_type);

#endif
