/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_to_str.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 11:56:56 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/13 15:53:30 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenize.h"

bool	is_directory(const char *map_name)
{
	int	map_fd;

	map_fd = open(map_name, O_DIRECTORY);
	if (map_fd == -1)
		return (false);
	close(map_fd);
	return (true);
}

int	get_map_fd(const char *map_name)
{
	int	map_fd;

	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Error: open()");
		exit(EXIT_FAILURE);
	}
	return (map_fd);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*helper_file_to_str(char *s1, const char *s2)
{
	char	*joined_str;
	size_t	len_s1;
	size_t	len_s2;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		len_s1 = 0;
	else
		len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	joined_str = malloc((len_s1 + len_s2 + 1 * sizeof(char)));
	if (joined_str == NULL)
		return (NULL);
	ft_strcpy(joined_str, s1);
	ft_strcpy(joined_str + len_s1, s2);
	free(s1);
	return (joined_str);
}

int	file_to_str(int fd, char **file_str)
{
	int			n;
	static char	buf[BUFSIZ + 1];

	if (fd < 0 || fd > 1024 || BUFSIZ <= 0 || !file_str)
		return (-1);
	*file_str = NULL;
	n = 1;
	while (n > 0)
	{
		*file_str = helper_file_to_str(*file_str, buf);
		if (*file_str == NULL)
			return (-1);
		n = read(fd, buf, BUFSIZ);
		if (n == -1)
			return (-1);
		buf[n] = '\0';
	}
	return (0);
}
