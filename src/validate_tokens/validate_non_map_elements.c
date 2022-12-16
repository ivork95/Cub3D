/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_non_map_elements.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:18:26 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/16 15:02:43 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "validate_tokens.h"

bool	has_four_cardinals(t_map_element *map_element)
{
	int	c;

	c = 0;
	while (map_element)
	{
		if (map_element->type == E_CARDINAL)
			c++;
		map_element = map_element->next;
	}
	if (c == 4)
		return (true);
	return (false);
}

bool	has_two_fcs(t_map_element *map_element)
{
	int	c;

	c = 0;
	while (map_element)
	{
		if (map_element->type == E_FLOOR_CEILING)
			c++;
		map_element = map_element->next;
	}
	if (c == 2)
		return (true);
	return (false);
}

static void	helper_cardinals(char *first_part, t_has_c *data)
{
	if (!ft_strncmp(first_part, "NO\0", 3))
		data->has_no = true;
	else if (!ft_strncmp(first_part, "SO\0", 3))
		data->has_so = true;
	else if (!ft_strncmp(first_part, "WE\0", 3))
		data->has_we = true;
	else if (!ft_strncmp(first_part, "EA\0", 3))
		data->has_ea = true;
}

bool	has_four_unique_cardinals(t_map_element *map_element)
{
	t_has_c	data;
	char	**splitted_array;

	init_has_c(&data);
	splitted_array = 0;
	while (map_element)
	{
		if (map_element->type == E_CARDINAL)
		{
			splitted_array = ft_split(map_element->map_element, ' ');
			if (count_ptrs(splitted_array) != 2)
			{
				free_splitted_array(splitted_array);
				return (false);
			}
			helper_cardinals(splitted_array[0], &data);
			free_splitted_array(splitted_array);
		}
		map_element = map_element->next;
	}
	return (data.has_no && data.has_so && data.has_we && data.has_ea);
}

/*
Moet nog getest worden
*/
bool	has_two_unique_fcs(t_map_element *map_element)
{
	bool	has_floor;
	bool	has_ceiling;
	char	**splitted_array;

	has_floor = false;
	has_ceiling = false;
	while (map_element)
	{
		if (map_element->type == E_FLOOR_CEILING)
		{
			splitted_array = ft_split(map_element->map_element, ' ');
			if (!splitted_array)
			{
				perror("Error\nmalloc()");
				exit(EXIT_FAILURE);
			}
			if (!ft_strncmp(splitted_array[0], "F\0", 2))
				has_floor = true;
			else if (!ft_strncmp(splitted_array[0], "C\0", 2))
				has_ceiling = true;
			free_splitted_array(splitted_array);
		}
		map_element = map_element->next;
	}
	return (has_floor && has_ceiling);
}
