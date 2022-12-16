/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:57:43 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/16 15:27:58 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	strip_spaces(char *s)
{
	char	*p2;

	if (!s)
		return (1);
	while (*s)
	{
		if (isspace(*s))
		{
			p2 = s;
			while (isspace(*p2))
				p2++;
			ft_memcpy(s, p2, strlen(s));
		}
		s++;
	}
	return (0);
}

int	convert_to_int(char *str)
{
	char	*endptr;
	long	val;

	errno = 0;
	val = ft_strtol(str, &endptr);
	if (errno != 0)
		put_exit_fail("Error\nstrtol()");
	if (endptr == str)
		put_exit_fail("Error\nno digits were found\n");
	if (*endptr != '\0')
	{	
		printf("Error\nfound characters after number: \"%s\"\n", endptr);
		exit(EXIT_FAILURE);
	}
	if (val < INT_MIN || val > INT_MAX)
		put_exit_fail("Error\nint overflow/underflow\n");
	if (val < 0 || val > 255)
		put_exit_fail("Error\nint not between 8 bits\n");
	return ((int) val);
}

t_rgb	build_rgb(char *str)
{
	char	**splitted_array;
	t_rgb	rgb;

	if (*str != 'F' && *str != 'C')
		put_exit_fail("Error\ninvalid floor ceiling string\n");
	str++;
	splitted_array = ft_split(str, ',');
	if (!splitted_array)
		put_exit_fail("Error\nmalloc failed");
	if (count_ptrs(splitted_array) != 3)
		put_exit_fail("Error\ninvalid floor ceiling string\n");
	rgb.r = convert_to_int(splitted_array[0]);
	rgb.g = convert_to_int(splitted_array[1]);
	rgb.b = convert_to_int(splitted_array[2]);
	free_splitted_array(splitted_array);
	return (rgb);
}

t_rgb	parse_floor_ceiling(t_map_element *map_element, int sub_type)
{
	while (map_element)
	{
		if (map_element->sub_type == sub_type)
			break ;
		map_element = map_element->next;
	}
	if (!map_element)
		put_exit_fail("Error\nparser()");
	strip_spaces(map_element->map_element);
	return (build_rgb(map_element->map_element));
}

char	**parse_cordinal(t_map_element *map_element, int sub_type)
{
	char	**splitted_array;

	while (map_element)
	{
		if (map_element->sub_type == sub_type)
			break ;
		map_element = map_element->next;
	}
	if (!map_element)
		put_exit_fail("Error\nparser()");
	splitted_array = ft_split(map_element->map_element, ' ');
	if (!splitted_array)
		put_exit_fail("Error\nmalloc()\n");
	return (splitted_array);
}
