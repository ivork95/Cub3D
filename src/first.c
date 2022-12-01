#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/parse.h"
#include "../includes/tokenize.h"
#include "../includes/validate_tokens.h"

/*
Your program must take as a first argument a scene description file with the .cub
extension.
*/
bool	is_dot_cub_file(char *arg)
{
	size_t	len;
	char	*extension;

	len = ft_strlen(arg);
	if (len < 4)
		return (false);
	extension = arg + len - 4;
	if (ft_strncmp(extension, ".cub\0", 5))
		return (false);
	return (true);
}

/*
Except for the map content, each type of element can be separated by one or
more empty line(s).
*/
t_map_element	*tokenizer(const char *map_name)
{
	int				map_fd;
	char			*file_str;
	char			**split_a;
	int				i;
	t_map_element	*map_elements;

	map_fd = get_map_fd(map_name);
	file_to_str(map_fd, &file_str);
	split_a = ft_split(file_str, '\n');
	if (!split_a)
		put_exit_fail("Error: ft_split()\n");
	i = 0;
	map_elements = 0;
	while (split_a[i])
	{
		inner_tokenizer(split_a[i], &map_elements);
		i++;
	}
	free_splitted_array(split_a);
	free(file_str);
	return (map_elements);
}

/*
Todo: check voor minimum aantal bytes van een 
valid map (kleinste paths + kleinste map)
*/
void	validate_tokens(t_map_element *map_element)
{
	if (!has_four_cardinals(map_element))
		put_exit_fail("Error: not 4 cardinals\n");
	if (!has_two_fcs(map_element))
		put_exit_fail("Error: not 2 floor ceilings\n");
	if (!has_three_map_elements_min(map_element))
		put_exit_fail("Error: less than 3 map elements\n");
	if (!is_sorted(map_element))
		put_exit_fail("Error: elements not sorted correctly\n");
	if (!has_four_unique_cardinals(map_element))
		put_exit_fail("Error: not 4 unique cardinals or valid cardinals\n");
	if (!has_two_unique_fcs(map_element))
		put_exit_fail("Error: not 2 unique floor ceilings \
			or valid floor ceilings\n");
	if (has_invalid_chars(map_element))
		put_exit_fail("Error: map contains invalid chars\n");
	if (!has_single_start_position(map_element))
		put_exit_fail("Error: not 1 start position\n");
}

t_cub	*parser(t_map_element *map_element)
{
	t_cub	*cub;
	char	**map_dup;

	cub = malloc(sizeof(*cub));
	if (!cub)
		put_exit_fail("Error: malloc()");
	cub->rows = get_map_size(map_element);
	cub->cols = get_map_col_size(map_element);
	cub->map = ll_to_a_map(map_element);
	map_dup = ll_to_a_map(map_element);
	get_start_pos(cub->map, cub->start_pos);
	cub->map[cub->start_pos[0]][cub->start_pos[1]] = '0';
	if (!itter_floodfill(map_dup, cub->start_pos, cub->rows, cub->cols))
		put_exit_fail("Error: map is not closed\n");
	free_splitted_array(map_dup);
	cub->floor = parse_floor_ceiling(map_element, SUB_FLOOR);
	cub->ceiling = parse_floor_ceiling(map_element, SUB_CEILING);
	cub->no_path = parse_cordinal(map_element, SUB_NO);
	cub->so_path = parse_cordinal(map_element, SUB_SO);
	cub->we_path = parse_cordinal(map_element, SUB_WE);
	cub->ea_path = parse_cordinal(map_element, SUB_EA);
	return (cub);
}

t_cub	*first(char *file_name)
{
	t_map_element	*map_element;
	t_cub			*cub;

	if (!is_dot_cub_file(file_name))
		put_exit_fail("Error: invalid file extension\n");
	map_element = tokenizer(file_name);
	if (!map_element)
		put_exit_fail("Error: no map_elements\n");
	validate_tokens(map_element);
	cub = parser(map_element);
	free_map_elements(map_element);
	print_cub(cub);
	printf("Map is valid!\n");
	return (cub);
}