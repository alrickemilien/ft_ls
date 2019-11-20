/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 18:35:27 by aemilien          #+#    #+#             */
/*   Updated: 2018/10/27 14:59:50 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "color.h"

static char	*append_color(char *str, char *color)
{
	char		*ret;
	size_t	len;

	len = ft_strlen(str) + ft_strlen(color) + ft_strlen(DEFAULT) + 1;
	if (!(ret = (char*)malloc(len * sizeof(char))))
		return (NULL);
	ft_bzero(ret, len);
	ft_memcpy(ret, color, ft_strlen(color));
	ft_memcpy(ret + ft_strlen(color), str, ft_strlen(str));
	ft_memcpy(ret + ft_strlen(color) + ft_strlen(str),
			DEFAULT,
			ft_strlen(DEFAULT));
	return (ret);
}

static char	*get_colored_file_path(struct stat *file, char *str)
{
	char	*color;

	if ((file->st_mode & S_IFMT) == S_IFDIR && file->st_mode & S_IWOTH)
		color = OTHER_USERS_WRITE_PERMISSION_DIRECTORY_COLOR;
	else if ((file->st_mode & S_IFMT) == S_IFDIR)
		color = DIRECTORY_COLOR;
	else if ((file->st_mode & S_IFMT) == S_IFLNK)
		color = LINK_COLOR;
	else if ((file->st_mode & S_IFMT) == S_IFREG && file->st_mode & S_IXOTH)
		color = OTHER_USERS_EXEC_PERMISSION_FILE_COLOR;
	else if (((file->st_mode & S_IFMT) == S_IFCHR)
			|| ((file->st_mode & S_IFMT) == S_IFBLK))
		color = CHARACTER_DEVICE_COLOR;
	else if ((file->st_mode & S_IFMT) == S_IFSOCK)
		color = SOCKET_COLOR;
	else
		return (ft_strdup(str));
	((t_stat*)file)->color_buffsize = ft_strlen(color) + ft_strlen(DEFAULT);
	return (append_color(str, color));
}

static char	*get_link(t_options *options, struct stat *file)
{
	char	*link;
	int		len;
	int		buffsize;
	int		is_tty;

	is_tty = options->is_tty;
	buffsize = 514;
	if (!(link = ft_strnew(buffsize)))
		return (NULL);
	if ((len = readlink(((t_stat *)file)->path, link, 514)) == -1
		&& len != buffsize)
		return (NULL);
	if (is_tty && (struct stat *)((t_stat *)file)->link)
		recycle(&link,
		get_colored_file_path((struct stat *)((t_stat *)file)->link, link));
	return (link);
}

/*
** Prints size of a file
*/

char		*get_file_path(t_options *options, struct stat *file)
{
	char	*buf;
	int		buffsize;
	int		is_tty;
	char	*tmp_link_colored;

	is_tty = options->is_tty;
	buffsize = 514;
	if (!(buf = ft_strnew(buffsize)))
		return (NULL);
	ft_bzero(buf, buffsize);
	ft_memcpy(buf, ((t_stat *)file)->name, ft_strlen(((t_stat *)file)->name));
	if (is_tty)
		recycle(&buf, get_colored_file_path(file, buf));
	if (options->listing && (file->st_mode & S_IFMT) == S_IFLNK)
	{
		recycle(&buf, ft_strjoin(buf, " -> "));
		tmp_link_colored = get_link(options, file);
		recycle(&buf, ft_strjoin(buf, tmp_link_colored));
		free(tmp_link_colored);
	}
	return (buf);
}
