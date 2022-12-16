/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_elements.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 16:28:12 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/16 14:42:44 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/validate_tokens.h"

void	init_has_c(t_has_c *data)
{
	data->has_no = false;
	data->has_so = false;
	data->has_we = false;
	data->has_ea = false;
}

bool	is_sorted(t_map_element *map_element)
{
	bool	has_encountered_type_three;

	has_encountered_type_three = false;
	while (map_element)
	{
		if (map_element->type == E_MAP)
			has_encountered_type_three = true;
		if (has_encountered_type_three && map_element->type < E_MAP)
			return (false);
		map_element = map_element->next;
	}
	return (true);
}

bool	has_three_map_elements_min(t_map_element *map_element)
{
	int	c;

	c = 0;
	while (map_element)
	{
		if (map_element->type == E_MAP)
			c++;
		map_element = map_element->next;
	}
	if (c >= 3)
		return (true);
	return (false);
}

bool	has_invalid_chars(t_map_element *map_element)
{
	char	*dup;

	while (map_element)
	{
		if (map_element->type == E_MAP)
		{
			dup = map_element->map_element;
			while (*dup)
			{
				if (*dup != ' ' && *dup != '0' && *dup != '1' && *dup != 'N'
					&& *dup != 'S' && *dup != 'E' && *dup != 'W')
					return (true);
				dup++;
			}
		}
		map_element = map_element->next;
	}
	return (false);
}

bool	has_single_start_position(t_map_element *map_element)
{
	char	*dup;
	int		encounters;

	encounters = 0;
	while (map_element)
	{
		if (map_element->type == E_MAP)
		{
			dup = map_element->map_element;
			while (*dup)
			{
				if (*dup == 'N' || *dup == 'S' || *dup == 'E' || *dup == 'W')
					encounters++;
				dup++;
			}
		}
		map_element = map_element->next;
	}
	if (encounters != 1)
		return (false);
	return (true);
}
