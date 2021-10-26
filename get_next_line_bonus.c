/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:21:39 by oronda            #+#    #+#             */
/*   Updated: 2021/10/26 09:37:10 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	has_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_file(int fd, char *savedbuffer, char *buff)
{
	int	r;

	r = 1;
	while (!has_newline(savedbuffer) && r > 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r > 0)
		{
			buff[r] = '\0';
			savedbuffer = ft_strjoin(savedbuffer, buff);
		}
	}
	if (*savedbuffer == '\0')
	{
		free(savedbuffer);
		return (NULL);
	}
	return (savedbuffer);
}

char	*cut_before_newline(char *buffer)
{
	int		i;
	char	*result;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	result = ft_substr(buffer, 0, i + 1);
	return (result);
}

char	*cut_after_newline(char *buffer)
{
	int		i;
	int		strlen;
	char	*result;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	strlen = ft_strlen(buffer);
	result = ft_substr(buffer, i + 1, strlen - i);
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*savedbuffer[1024];
	char		buff[BUFFER_SIZE + 1];
	char		*result;

	result = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (NULL);
	if (savedbuffer[fd])
	{
		savedbuffer[fd] = read_file(fd, savedbuffer[fd], buff);
		result = cut_before_newline(savedbuffer[fd]);
		savedbuffer[fd] = cut_after_newline(savedbuffer[fd]);
	}
	else
	{
		savedbuffer[fd] = ft_strdup("");
		savedbuffer[fd] = read_file(fd, savedbuffer[fd], buff);
		if (savedbuffer[fd])
		{
			result = cut_before_newline(savedbuffer[fd]);
			savedbuffer[fd] = cut_after_newline(savedbuffer[fd]);
		}
	}
	return (result);
}
