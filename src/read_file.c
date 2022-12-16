/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 00:07:49 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/16 15:42:19 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "validate_tokens.h"
#include "tokenize.h"
#include "parse.h"

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

t_map_element	*tokenizer(const char *map_name)
{
	int				map_fd;
	char			*file_str;
	char			**split_a;
	int				i;
	t_map_element	*map_elements;

	if (is_directory(map_name))
		put_exit_fail("Error\nArg is directory\n");
	map_fd = get_map_fd(map_name);
	file_to_str(map_fd, &file_str);
	split_a = ft_split(file_str, '\n');
	if (!split_a)
		put_exit_fail("Error\nft_split()\n");
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

void	validate_tokens(t_map_element *map_element)
{
	if (!has_four_cardinals(map_element))
		put_exit_fail("Error\nnot 4 cardinals\n");
	if (!has_two_fcs(map_element))
		put_exit_fail("Error\nnot 2 floor ceilings\n");
	if (!has_three_map_elements_min(map_element))
		put_exit_fail("Error\nless than 3 map elements\n");
	if (!is_sorted(map_element))
		put_exit_fail("Error\nelements not sorted correctly\n");
	if (!has_four_unique_cardinals(map_element))
		put_exit_fail("Error\nnot 4 unique cardinals or valid cardinals\n");
	if (!has_two_unique_fcs(map_element))
		put_exit_fail("Error\nnot 2 unique floor ceilings \
			or valid floor ceilings\n");
	if (has_invalid_chars(map_element))
		put_exit_fail("Error\nmap contains invalid chars\n");
	if (!has_single_start_position(map_element))
		put_exit_fail("Error\nnot 1 start position\n");
}

t_cub	*parser(t_map_element *map_element)
{
	t_cub	*cub;
	char	**map_dup;

	cub = malloc(sizeof(*cub));
	if (!cub)
		put_exit_fail("Error\nmalloc()");
	cub->rows = get_map_size(map_element);
	cub->cols = get_map_col_size(map_element);
	cub->map = ll_to_a_map(map_element);
	map_dup = ll_to_a_map(map_element);
	get_start_pos(cub->map, cub->start_pos);
	cub->orientation = cub->map[cub->start_pos[0]][cub->start_pos[1]];
	cub->map[cub->start_pos[0]][cub->start_pos[1]] = '0';
	if (!itter_floodfill(map_dup, cub->start_pos, cub->rows, cub->cols))
		put_exit_fail("Error\nmap is not closed\n");
	free_splitted_array(map_dup);
	cub->floor = parse_floor_ceiling(map_element, SUB_FLOOR);
	cub->ceiling = parse_floor_ceiling(map_element, SUB_CEILING);
	cub->no_path = parse_cordinal(map_element, SUB_NO);
	cub->so_path = parse_cordinal(map_element, SUB_SO);
	cub->we_path = parse_cordinal(map_element, SUB_WE);
	cub->ea_path = parse_cordinal(map_element, SUB_EA);
	return (cub);
}

t_cub	*read_file(char *file_name)
{
	t_map_element	*map_element;
	t_cub			*cub;

	if (!is_dot_cub_file(file_name))
		put_exit_fail("Error\ninvalid file extension\n");
	map_element = tokenizer(file_name);
	if (!map_element)
		put_exit_fail("Error\nno map_elements\n");
	validate_tokens(map_element);
	cub = parser(map_element);
	free_map_elements(map_element);
	return (cub);
}
