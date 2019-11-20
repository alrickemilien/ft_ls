#include "ft_ls.h"


/*
** Stat on the link pointed by the t_stat structure passed as aprameter
** Fill its link structure
** !! WARNING !! it uses the already given path of the t_stat structure
*/

int read_link_stat(t_stat  *file, bool do_fail)
{
	if((ACCESS_STATS(file)->st_mode & S_IFMT) == S_IFLNK) {
		// Allocate memory for inside struct stat * ptr
		if ((file->link = (t_stat*)malloc(sizeof(t_stat))) == NULL) {
			print_error_on_file(
				"ft_ls: not enough memory",
				file->path);

			return (EXIT_SERIOUS_FAILURE);
		}

		ft_bzero(file->link, sizeof(t_stat));

		file->link->path = get_link_path(file->path);
		file->link->name = get_filename_from_path(file->path);

		// Get stat of the link
		if (stat(file->path, (struct stat *)file->link) == -1) {
			delete_file_link(file->link);
			file->link = NULL;

			if (do_fail) {
				print_error_on_file("ft_ls: cannot access link",
					file->link->path);

				return (EXIT_MINOR_FAILURE);
			}
		}
	}

	return (EXIT_OK);
}

/*
** Simple stat on a t_stat structure
** !! WARNING !! it uses the already given path of the t_stat structure
*/

int read_file_stat(t_stat *file)
{
	if (lstat(file->path, (struct stat *) file) == -1) {
		print_error_on_file(
			ERROR_NOT_A_DIRECTORY,
			file->path);

		return (EXIT_MINOR_FAILURE);
	}
	return (EXIT_OK);
}

/*
** Check if the parameter is an option
** return 1 if its something like -Pezfz or --fgzegze
** return 0 if it is something like Makefile or - or --
*/

int is_an_option(const char *name)
{
	if ((name[0] == '-' && name[1] != '-')
		|| (name[0] == '-' && name[1] == '-')) {
		return (1);
	}

	return (0);
}


int is_dot_file(const char *name) {
 if (name[0] == '.') {
    return (1);
 }

 return (0);
}

int is_dot_directory(const char *name) {
 if (!ft_strcmp(name, "..") || !ft_strcmp(name, ".")) {
    return (1);
 }

 return (0);
}
