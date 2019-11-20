#include "ft_ls.h"

static void *get_varxattr(t_stat *p, char *list, ssize_t listxattr_size) {
	ssize_t getxattr_size;
	char *value;
	int i;
	char *name;

	i = 0;
	while (i < listxattr_size) {
		// Get the size of the attribute
		if ((getxattr_size = GETXATTR(((t_stat*)p)->path, list + i, NULL, 0)) == -1) {
			break;
		}

		// Allocate this size
		if (!(value = (char*)malloc(getxattr_size * sizeof(char)))) {
			return (NULL);
		}

		name = ft_strdup(list);
		// Fill the buffer with the value of the attr
		if (GETXATTR(((t_stat*)p)->path, list + i, value, getxattr_size) == -1) {
			return (NULL);
		}

		ft_putstr("\t");
		ft_putstr(name);
		ft_putstr(" ");
		ft_putstr(value);
		ft_putstr(" ");
		recycle(&name, ft_itoa((int)getxattr_size));
		ft_putstr(name);
		ft_putendl("");

		free(name);
		free(value);

		i += ft_strlen(list);
	}

	return (NULL);
}

static void *get_link_varxattr(t_stat *p, char *list, ssize_t listxattr_size) {
	ssize_t getxattr_size;
	char *value;
	int i;
	char *name;

	i = 0;
	while (i < listxattr_size) {
		// Get the size of the attribute
		if ((getxattr_size = LGETXATTR(((t_stat*)p)->path, list + i, NULL, 0)) == -1) {
			break;
		}

		// Allocate this size
		if (!(value = (char*)malloc(getxattr_size * sizeof(char)))) {
			return (NULL);
		}

		name = ft_strdup(list);
		// Fill the buffer with the value of the attr
		if (LGETXATTR(((t_stat*)p)->path, list + i, value, getxattr_size) == -1) {
			return (NULL);
		}

		ft_putstr("\t");
		ft_putstr(name);
		ft_putstr("  ");
		ft_putstr(value);
		ft_putstr("  ");
		recycle(&name, ft_itoa((int)getxattr_size));
		ft_putendl(name);

		free(name);
		free(value);

		i += ft_strlen(list) + 1;
	}

	return (NULL);
}

void list_file_xattr(t_options *options, struct stat *p)
{
	(void)options;

	if ((p->st_mode & S_IFMT ) == S_IFLNK) {
		get_link_varxattr((t_stat*)p, ((t_stat*)p)->listxattr, ((t_stat*)p)->listxattr_size);
		return;
	}

	get_varxattr((t_stat*)p, ((t_stat*)p)->listxattr, ((t_stat*)p)->listxattr_size);
}

static char *get_link_extended_attributes(t_options *options, struct stat *p) {
	ssize_t listxattr_size;
	char *list;

		(void)options;

		if ((listxattr_size = LLISTXATTR(((t_stat*)p)->path, NULL, 0)) == -1) {
			return (ft_strdup(""));
		}

		// Allocate this size
		if (!(list = (char*)malloc(listxattr_size * sizeof(char)))) {
			return (NULL);
		}

		if ((listxattr_size = LLISTXATTR(((t_stat*)p)->path, list, listxattr_size)) == -1) {
			return (ft_strdup(""));
		}

		((t_stat*)p)->listxattr = list;
		((t_stat*)p)->listxattr_size = listxattr_size;

		if (listxattr_size > 0) {
			return (ft_strdup(EXTENDED_ATTRIBUTE_CHARACTER));
		}

		return (ft_strdup(""));
}

/*
** Prints the extended attributes for character devices
** check ACL
*/

char *get_file_extended_attributes(t_options *options, struct stat *p) {
	ssize_t listxattr_size;
	char *list;

	if (!options->listing)
		return ft_strdup("");

	// When the node is a link
	if ((p->st_mode & S_IFMT ) == S_IFLNK) {
		return get_link_extended_attributes(options, p);
	}

	if ((listxattr_size = LISTXATTR(((t_stat*)p)->path, NULL, 0)) == -1) {
		return (ft_strdup(""));
	}

	// Allocate this size
	if (!(list = (char*)malloc(listxattr_size * sizeof(char)))) {
		return (NULL);
	}

	if ((listxattr_size = LISTXATTR(((t_stat*)p)->path, list, listxattr_size)) == -1) {
		free(list);
		return (ft_strdup(""));
	}

	if (listxattr_size > 0) {
		((t_stat*)p)->listxattr = list;
		((t_stat*)p)->listxattr_size = listxattr_size;

		return (ft_strdup(EXTENDED_ATTRIBUTE_CHARACTER));
	}

	free(list);

	#ifdef __APPLE__
	char *acl;

	acl = get_file_acl(options, p);
	if (acl)
		return acl;
	#endif

	return (ft_strdup(""));
}
