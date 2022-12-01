/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_elements.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 16:28:12 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/01 12:26:22 by ivork         ########   odam.nl         */
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

/*
Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
*/
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

/*
The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.
Moet nog getest worden
*/
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
