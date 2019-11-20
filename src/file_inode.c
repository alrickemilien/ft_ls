#include "ft_ls.h"
#include "color.h"

/*
** This function returns a buffer with inode number
*/

char *get_file_inode(t_options *options, struct stat *p)
{
 	if (!options->inode)
  		return ft_strdup("");

	return (ft_itoa((int)p->st_ino));
}
