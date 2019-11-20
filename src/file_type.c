#include "ft_ls.h"
#include "color.h"

static char *char_to_string(char c) {
	char *ret;

	if (!(ret = ft_strnew(1))) return NULL;

	ret[0] = c;

	return (ret);
}

/*
 **  S_IFSOCK   0140000   socket
 **  S_IFLNK    0120000   symbolic link
 **  S_IFREG    0100000   regular file
 **  S_IFBLK    0060000   block device
 **  S_IFDIR    0040000   directory
 **  S_IFCHR    0020000   character device
 **  S_IFIFO    0010000   FIFO
 */

char* get_file_type(t_options *options, struct stat *p) {
	char c;

	if (!options->listing)
		return ft_strdup("");

	if ((p->st_mode & S_IFMT) == S_IFSOCK)
		c = 's';
	else if ((p->st_mode & S_IFMT) == S_IFREG)
		c = '-';
	else if ((p->st_mode & S_IFMT) == S_IFLNK)
		c = 'l';
	else if ((p->st_mode & S_IFMT) == S_IFBLK)
		c = 'b';
	else if ((p->st_mode & S_IFMT) == S_IFDIR)
		c = 'd';
	else if ((p->st_mode & S_IFMT) == S_IFCHR)
		c = 'c';
	else if ((p->st_mode & S_IFMT) == S_IFIFO)
		c = 'f';
	else
		c = '-';

	return char_to_string(c);
}
