#include "ft_ls.h"
#include "color.h"

/*
** Prints size of a file
*/
char *get_file_link_number(t_options *options, struct stat *p) {
	if (!options->listing)
		return (ft_strdup(""));

	return (ft_itoa(p->st_nlink));
}
