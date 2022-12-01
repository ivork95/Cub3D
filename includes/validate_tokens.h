/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_tokens.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 12:23:01 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/01 12:02:13 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_TOKENS_H
# define VALIDATE_TOKENS_H

/* Public libaries */

/* Private libaries */
# include "structs.h"
# include "tokenize.h"

/* floodfill.c */
int		get_start_pos(char **two_d_a, int start_pos[2]);
bool	itter_floodfill(char *map[], int pos[2], int rows, int cols);

/* validate_map_elements.c */
void	init_has_c(t_has_c *data);
bool	is_sorted(t_map_element *map_element);
bool	has_three_map_elements_min(t_map_element *map_element);
bool	has_invalid_chars(t_map_element *map_element);
bool	has_single_start_position(t_map_element *map_element);

/* validate_non_map_elements.c */
bool	has_four_cardinals(t_map_element *map_element);
bool	has_two_fcs(t_map_element *map_element);
bool	has_four_unique_cardinals(t_map_element *map_element);
bool	has_two_unique_fcs(t_map_element *map_element);

#endif /* validate_tokens.h */
