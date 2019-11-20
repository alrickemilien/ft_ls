#include "ft_ls.h"
#include "color.h"

static inline void fill_owner_file_permission(struct stat *p, char *buffer) {
	if (p->st_mode & S_IRUSR)
		buffer[0] = 'r';
	else
		buffer[0] = '-';

	if (p->st_mode & S_IWUSR)
		buffer[1] = 'w';
	else
		buffer[1] = '-';

	if (p->st_mode & S_IXUSR && p->st_mode & S_ISUID)
		buffer[2] = 'w';
	else if(p->st_mode & S_IXUSR)
		buffer[2] = 'x';
	else if(p->st_mode & S_ISUID)
		buffer[2] = 'S';
	else
		buffer[2] = '-';
}

static inline void fill_group_file_permission(struct stat *p, char *buffer) {
	if (p->st_mode & S_IRGRP)
		buffer[0] = 'r';
	else
		buffer[0] = '-';

	if (p->st_mode & S_IWGRP)
		buffer[1] = 'w';
	else
		buffer[1] = '-';

	if (p->st_mode & S_IXGRP && p->st_mode & S_ISGID)
		buffer[2] = 's';
	else if(p->st_mode & S_IXGRP)
		buffer[2] = 'x';
	else if(p->st_mode & S_ISGID)
		buffer[2] = 'S';
	else
		buffer[2] = '-';
}

static inline void fill_other_file_permission(struct stat *p, char *buffer) {
	if (p->st_mode & S_IROTH)
		buffer[0] = 'r';
	else
		buffer[0] = '-';

	if (p->st_mode & S_IWOTH)
		buffer[1] = 'w';
	else
		buffer[1] = '-';

	if (p->st_mode & S_IXOTH && p->st_mode & S_ISVTX)
		buffer[2] = 't';
	else if(p->st_mode & S_IXOTH)
		buffer[2] = 'x';
	else if(p->st_mode & S_ISVTX)
		buffer[2] = 'T';
	else
		buffer[2] = '-';
}

/*
** This function returns a buffer of file permissions
** like rwxrwxr-x+
*/

char *get_file_permissions(t_options *options, struct stat *p) {
	char *buffer;
	char *xattr_character;

	if (!options->listing)
		return ft_strdup("");

	buffer = ft_strnew(9);

	fill_owner_file_permission(p, buffer);
	fill_group_file_permission(p, buffer + 3);
	fill_other_file_permission(p, buffer + 6);

	xattr_character = get_file_extended_attributes(options, p);

	recycle(&buffer, ft_strjoin(buffer, xattr_character));

	free(xattr_character);

	return (buffer);
}
