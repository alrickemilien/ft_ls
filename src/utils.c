#include "ft_ls.h"
#include "color.h"

char *get_link_path(char *path_of_link)
{
	int len;
	char *ret;
	char *tmp;
	int BUFFSIZE;

	BUFFSIZE = 255;

	if ((ret = ft_strnew(BUFFSIZE)) == NULL)
		return (NULL);

	if ((len = readlink(path_of_link, ret, BUFFSIZE)) == -1)
		return (NULL);

	if (len > BUFFSIZE)
		return (NULL);

	if (BUFFSIZE != len) {
		if ((tmp = ft_strnew(len)) == NULL)
			return (NULL);
		ft_memcpy(tmp, ret, len);

		recycle(&ret, tmp);
	}

	return (ret);
}

/*
** Print a styled error with name of file
*/

void print_error_on_file(const char *error_msg, const char *name) {
	char *tmp;

	const char *strings[4] = {
		error_msg,
		" '",
		name,
		"'",
	};

	tmp = create_string_from_many(strings, 4);

	perror(tmp);

	if (tmp == NULL) return;

	free(tmp);
}

/*
** Print a styled error with name of file
*/
void print_error_on_option(const char *error_msg, const char *name) {
	char *tmp;
	const char *strings[4] = {
		error_msg,
		" '",
		name,
		"'",
	};

	tmp = create_string_from_many(strings, 4);

	ft_putstr(tmp);
	ft_putchar('\n');

	if (tmp == NULL) return;

	free(tmp);
}


/*
** This function create a real path of a file from its directory
*/

char *path_from_dir(const char *dirname, const char *filename) {
    char *tmp;

    tmp = NULL;

    if (dirname[ft_strlen(dirname) - 1] == '/') {
        return ft_strjoin(dirname, filename);
    }

    recycle(&tmp, ft_strjoin(dirname, "/"));
    recycle(&tmp, ft_strjoin(tmp, filename));


    return tmp;
}

int end_with_slash(const char * str)
{
	while (*str && *(str + 1))
		str++;

	if (*str == '/')
		return(1);

	return (0);
}

/*
** Get file name from path
** etc return etc
** /etc returns /etc
** /etc/system returns system
** /etc/system/ returns system
*/

char *get_filename_from_path(char *path)
{
	char		*ptr;
	char		*ret;
	size_t	i;

  ptr = path;

	while (*path)
	{
		if (*(path + 1) != 0 && *path == '/')
			ptr = path + 1;

		path++;
	}

	i = ft_strlen(ptr);

  ret = ft_strdup(ptr);

	if (ret[1] && ret[i-1] == '/')
		ret[i-1] = 0;


	return (ret);
}

/*
** Delete file link if there is one
*/

void delete_file_link(t_stat *link) {
	if (link == NULL)
		return ;

	if (link->path)
		free(link->path);
	if (link->name)
		free(link->name);
	free(link);
}

/*
** Function to give to ft_lstdel
*/

void delete_file_node(void *ptr, size_t size)
{
	(void)size;

	delete_file_link(((t_stat*)ptr)->link);

	if (((t_stat*)ptr)->buffer)
		free(((t_stat*)ptr)->buffer);

	if (((t_stat*)ptr)->name)
		free(((t_stat*)ptr)->name);

	if (((t_stat*)ptr)->path)
		free(((t_stat*)ptr)->path);

	if (((t_stat*)ptr)->listxattr)
		free(((t_stat*)ptr)->listxattr);

	free(ptr);
}
