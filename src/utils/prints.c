/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prints.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 18:37:22 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/01 12:25:43 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	print_splitted_a(char **split_a)
{
	int	i;

	i = 0;
	while (split_a[i])
	{
		printf("split_a[%i] \t= |%s|\n", i, split_a[i]);
		i++;
	}
}

void	print_map_elements(t_map_element *head)
{
	while (head)
	{
		printf("head->map_element = |%s|\n", head->map_element);
		printf("head->type = %i\n", head->type);
		head = head->next;
	}
}

void	print_rgb(t_rgb *rgb)
{
	printf("\t\t\t\tr = \t%i\n", rgb->r);
	printf("\t\t\t\tg = \t%i\n", rgb->g);
	printf("\t\t\t\tb = \t%i\n", rgb->b);
	printf("\t\t\t}\n");
}

void	print_cub(t_cub *cub)
{
	printf("cub\n");
	printf("{\n");
	printf("\trows = \t\t%i\n", cub->rows);
	printf("\tcols = \t\t%i\n", cub->cols);
	printf("\tmap = \t\t%p\n", cub->map);
	printf("\tstart_pos = \t[%i, %i]\n", cub->start_pos[0], cub->start_pos[1]);
	printf("\tno_path = \t%s\n", cub->no_path[1]);
	printf("\tso_path = \t%s\n", cub->so_path[1]);
	printf("\twe_path = \t%s\n", cub->we_path[1]);
	printf("\tea_path = \t%s\n", cub->ea_path[1]);
	printf("\tfloor = \t{\n");
	print_rgb(&(cub->floor));
	printf("\tceiling = \t{\n");
	print_rgb(&(cub->ceiling));
	printf("}\n");
}

void	put_exit_fail(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
