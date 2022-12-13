/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_to_a_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:44:36 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/13 16:17:40 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	get_map_size(t_map_element *map_element)
{
	int	map_size;

	map_size = 0;
	while (map_element)
	{
		if (map_element->type == E_MAP)
			map_size++;
		map_element = map_element->next;
	}
	return (map_size);
}

int	get_map_col_size(t_map_element *map_element)
{
	int	map_col_size;
	int	x;

	map_col_size = 0;
	while (map_element)
	{
		if (map_element->type == E_MAP && map_element->map_element)
		{
			x = ft_strlen(map_element->map_element);
			if (x > map_col_size)
				map_col_size = x;
		}
		map_element = map_element->next;
	}
	return (map_col_size);
}

static char	**calloc_a_map(t_map_element *map_element)
{
	int		map_size;
	char	**a_map;

	map_size = get_map_size(map_element);
	a_map = ft_calloc(map_size + 1, sizeof(*a_map));
	if (!a_map)
		return (0);
	return (a_map);
}

/*
Regel 83 zou weg kunnen. Maar dan zijn de characters
die de map opvullen om het vierkant te maken '\0' chars
*/
char	**ll_to_a_map(t_map_element *map_element)
{
	int		i;
	char	**a_map;
	int		map_col_size;

	i = 0;
	a_map = calloc_a_map(map_element);
	if (!a_map)
	{
		perror("Error\nmalloc()");
		exit(EXIT_FAILURE);
	}
	map_col_size = get_map_col_size(map_element);
	while (map_element)
	{
		if (map_element->type == E_MAP && map_element->map_element)
		{
			a_map[i] = ft_calloc(map_col_size + 1, sizeof(*(a_map[i])));
			ft_memset(a_map[i], 'X', map_col_size);
			ft_memcpy(a_map[i], map_element->map_element,
				ft_strlen(map_element->map_element));
			i++;
		}
		map_element = map_element->next;
	}
	return (a_map);
}
