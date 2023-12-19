/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:42:33 by livsauze          #+#    #+#             */
/*   Updated: 2023/12/18 12:34:35 by livsauze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *stash)
{
	int	char_read;

	char_read = 1;
	while (char_read > 0 && !ft_strchr(stash, '\n'))
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= -1)
			return (free(buf), free(stash), NULL);
		if (char_read > 0)
		{
			buf[char_read] = '\0';
			stash = ft_strjoin(stash, buf);
			if (!stash)
				return (free(buf), NULL);
		}
	}
	return (free(buf), stash);
}

char	*ft_get_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

char	*ft_clean_stash(char	*stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	new_stash = ft_substr(stash, i, ft_strlen(stash) - i + 1);
	if (!new_stash || new_stash[0] == '\0')
		return (free(new_stash), free(stash), NULL);
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stash = ft_read(fd, buf, stash);
	line = ft_get_line(stash);
	stash = ft_clean_stash(stash);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char *line;

	fd = open("test.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("ligne 1 : %s\n", line);
	free(line);
	line = NULL;
	
	line = get_next_line(fd);
	printf("ligne 2 : %s\n", line);
	free(line);
	line = NULL;
	
	line = get_next_line(fd);
	printf("ligne 3 : %s", line);
	free(line);
	line = NULL;

	line = get_next_line(fd);
	printf("ligne 4 : %s", line);
	free(line);
	line = NULL;

	line = get_next_line(fd);
	printf("ligne 5 : %s", line);
	free(line);
	line = NULL;
	
	close(fd);
	return (0);
}*/