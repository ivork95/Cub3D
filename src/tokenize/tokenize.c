/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 11:59:44 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/16 15:25:35 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static t_map_element	*init_map_element(char *map_element, int type,
	int sub_type)
{
	t_map_element	*node;

	node = malloc(sizeof(*node));
	if (!node)
		put_exit_fail("Error\nmalloc()\n");
	node->map_element = map_element;
	node->type = type;
	node->sub_type = sub_type;
	node->next = 0;
	return (node);
}

static void	map_elements_add_back(t_map_element **lst, t_map_element *new)
{
	t_map_element	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	tokenize_map_element(char *input_elem, int type,
	int sub_type, t_map_element **lst)
{
	char			*s;
	t_map_element	*node;

	s = strdup(input_elem);
	if (!s)
		put_exit_fail("Error\nmalloc()\n");
	node = init_map_element(s, type, sub_type);
	map_elements_add_back(lst, node);
}

void	inner_tokenizer(char *split_a_i, t_map_element **map_elements)
{
	if (ft_strnstr(split_a_i, "NO ", ft_strlen(split_a_i)))
		tokenize_map_element(split_a_i, E_CARDINAL, SUB_NO, map_elements);
	else if (ft_strnstr(split_a_i, "SO ", ft_strlen(split_a_i)))
		tokenize_map_element(split_a_i, E_CARDINAL, SUB_SO, map_elements);
	else if (ft_strnstr(split_a_i, "WE ", ft_strlen(split_a_i)))
		tokenize_map_element(split_a_i, E_CARDINAL, SUB_WE, map_elements);
	else if (ft_strnstr(split_a_i, "EA ", ft_strlen(split_a_i)))
		tokenize_map_element(split_a_i, E_CARDINAL, SUB_EA, map_elements);
	else if (ft_strnstr(split_a_i, "F ", ft_strlen(split_a_i)))
		tokenize_map_element(split_a_i, E_FLOOR_CEILING,
			SUB_FLOOR, map_elements);
	else if (ft_strnstr(split_a_i, "C ", ft_strlen(split_a_i)))
		tokenize_map_element(split_a_i, E_FLOOR_CEILING,
			SUB_CEILING, map_elements);
	else
		tokenize_map_element(split_a_i, E_MAP, 0, map_elements);
}
