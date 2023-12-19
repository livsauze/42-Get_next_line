/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livsauze <livsauze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:12:08 by livsauze          #+#    #+#             */
/*   Updated: 2023/12/18 12:34:48 by livsauze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[MAX_FD];
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash[fd]), stash[fd] = NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	stash[fd] = ft_read(fd, buf, stash[fd]);
	line = ft_get_line(stash[fd]);
	stash[fd] = ft_clean_stash(stash[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd1;
	int	fd2;
	char *line;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

	line = get_next_line(fd1);
	printf("FD 1, ligne 1 : %s\n", line);
	free(line);
	
	line = get_next_line(fd1);
	printf("FD 1, ligne 2 : %s\n", line);
	free(line);
	
	line = get_next_line(fd2);
	printf("FD 2, ligne 1 : %s\n", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD 2, ligne 2 : %s\n", line);
	free(line);

	close(fd1);
	close(fd2);
	return (0);
}*/
