#include "ft_ls.h"
#include "color.h"

/*
** with no tty, -l or -1, display row by row
*/

static void row_display(t_options *options, t_list *list) {
	while (list) {
		ft_putendl(((t_stat*)list->content)->buffer);

#ifdef __APPLE__
		if (options->listing && options->acl)
			list_file_acl(options, list->content);
#endif

		if (options->listing && options->xattr)
			list_file_xattr(options, list->content);

		list = list->next;
	}
}

void output_buffer(t_options *options, t_list *list)
{
	if (!list)
		return ;

	if (options->listing || options->simple_listing)
		return row_display(options, list);

	return columns_display(options, list);
}

/*
** @params
** DIR *directory : ptr on opended directory to read it
** char *dirname : name of directory in order to compute
** nested file path like dirname/filename1, dirname/filename2
**
** @return
** Returns a list containing t_stat structures
** for each nested files of the directory
*/

t_list *get_list_directorys_files(t_options *options,
																	DIR *directory,
																	const char *dirname)
{
	t_list					*list;
	t_stat					obj;
	struct dirent 	*dir;
	int exit_code;

	list = NULL;

	while ((dir = readdir(directory)) != NULL) {
		ft_bzero(&obj, sizeof(t_stat));

		if (options->all || !is_dot_file(dir->d_name)) {
			obj.path = path_from_dir(dirname, dir->d_name);
			obj.name = get_filename_from_path(obj.path);

			exit_code = read_file_stat(&obj);
			if (exit_code == EXIT_OK)
				exit_code = read_link_stat(&obj, false);
			if (exit_code == EXIT_OK)
			{
				ft_lstadd(&list, ft_lstnew(&obj, sizeof(t_stat)));
				continue;
			}

			free(obj.path);
			free(obj.name);
			delete_file_link((t_stat*)obj.link);
		}
  }

  return list;
}

static inline int is_directory(struct stat *p) {
	if ((p->st_mode & S_IFMT) == S_IFDIR) {
		return (1);
	}

	return (0);
}

/*
** Prints the number of 512 kB blocks allocated for the files
** in this folder
*/

static void print_total(t_list *list) {
	int total;

	if ((FT_LS_TARGET == TARGET_OSX) && !ft_lstlen(list)) {
		return;
	}

	total = 0;
	while (list) {
		// When the file is a link, handle specific case
		if ((((struct stat*)list->content)->st_blocks& S_IFMT) == S_IFLNK
			&& ACCESS_LINK_STATS((t_stat*)list->content)) {
			total += ACCESS_LINK_STATS((t_stat*)list->content)->st_blocks;
		}

		// When its a regular file or folder
		else if (!is_dot_directory(((t_stat*)list->content)->name)) {
			total += ((struct stat*)list->content)->st_blocks;
		}

		list = list->next;
	}

	ft_putstr("total ");
	ft_putnbr(total);
	ft_putendl("");
}

/*
** (1) open dir and return on error
** (2) loop over files in directory and store each stat in list
** (3) sort the list by filename (reversed order or not according to -r option)
** ?(4) If recursive option is set, call handle_directory on each sub folder
** (5) close dir at the end
*/

int handle_directory(t_options *options, t_stat *p)
{
	DIR *directory;
	t_list			*list;
	t_list			*tmp;

	if ((directory = opendir(p->path)) == NULL) {
		print_error_on_file(ERROR_NOT_A_DIRECTORY, p->path);
		return (EXIT_MINOR_FAILURE);
	}

	list = get_list_directorys_files(options, directory, p->path);

	sort_file_list(options, &list);

	if (options->print_dir_name || options->recursive) {
		if (options->print_dir_name) {
			ft_putstr(p->path);
			ft_putendl(" :");
		}

		options->print_dir_name = 1;
	}

	if (options->listing)
		print_total(list);

	create_output_buffer(options, list);

	output_buffer(options, list);

	if (options->recursive) {
		tmp = list;
		while (tmp) {
			if (is_directory(tmp->content) && !(is_dot_directory(((t_stat*)tmp->content)->name))) {
				ft_putendl("");
				handle_directory(options, tmp->content);
			}

			tmp = tmp->next;
		}
	}

	ft_lstdel(&list, &delete_file_node);

	closedir(directory);

	return (0);
}
