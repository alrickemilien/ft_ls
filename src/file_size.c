#include "ft_ls.h"
#include "color.h"


/*
** Prints the block, size size which is specific
** Use the major and minor macros of stat.h
** to get unsigned int values and print it
** https://askubuntu.com/questions/727728/size-of-device-file-missing-in-ls-l-output
** and
** https://stackoverflow.com/questions/35392291/how-to-convert-between-a-dev-t-and-major-minor-device-numbers
*/

char *get_block_file_size(struct stat *p) {
	char *major_str;
	char *minor_str;
	char *ret;

	ret = NULL;

	major_str = ft_itoa(major(p->st_rdev));
	minor_str = ft_itoa(minor(p->st_rdev));

	recycle(&ret, ft_strjoin(major_str, ", "));
	recycle(&ret, ft_strjoin(ret, minor_str));

	free(major_str);
	free(minor_str);

	return (ret);
}

/*
** Prints size of a file
*/

char *get_file_size(t_options *options, struct stat *p) {
	if (!options->listing)
		return ft_strdup("");

	if (((p->st_mode & S_IFMT) == S_IFBLK) || ((p->st_mode & S_IFMT) == S_IFCHR)) {
		return get_block_file_size(p);
	}

	return (ft_itoa(p->st_size));
}
