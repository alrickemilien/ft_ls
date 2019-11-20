#include "ft_ls.h"

int fill_list_stats(t_options *options,
										char *path,
										t_list **simple_files,
										t_list **directorys_files)
{
	t_stat 	file;
	int exit_code;

	ft_bzero(&file, sizeof(t_stat));


	file.path = ft_strdup(path);
	file.name = get_filename_from_path(path);

	if ((exit_code = read_file_stat(&file)) != EXIT_OK)
		return (exit_code);

	if ((exit_code = read_link_stat(&file, false)) != EXIT_OK)
		return (exit_code);

	if (options->listing && (ACCESS_STATS(&file)->st_mode & S_IFMT) == S_IFLNK && !end_with_slash(file.path)) {
		ft_lstadd(simple_files, ft_lstnew(&file, sizeof(t_stat)));
		return (EXIT_OK);
	}


	if (!options->only_directory && ((((ACCESS_STATS(&file)->st_mode & S_IFMT) == S_IFDIR))
		|| (!options->inode && file.link && ((((struct stat *)file.link)->st_mode & S_IFMT) == S_IFDIR)))) {
		ft_lstadd(directorys_files, ft_lstnew(&file, sizeof(t_stat)));
	} else {
		ft_lstadd(simple_files, ft_lstnew(&file, sizeof(t_stat)));
	}

	return (EXIT_OK);
}

/*
** Create default dir as parameter, which is dot dirsctory
** When only directory option is set (-d)
** add the folder to simple_file list
** In this case, the content of the current directory will be not displayed
*/

static int get_default_directory(t_options *options, t_list **directorys_files, t_list **simple_files) {
	t_stat				obj;
	int exit_code;

	ft_bzero(&obj, sizeof(t_stat));

	obj.path = ft_strdup(".");
	obj.name = get_filename_from_path(obj.path);

	if ((exit_code = read_file_stat(&obj)) != EXIT_OK)
		return (exit_code);

	if (options->only_directory)
		ft_lstadd(simple_files, ft_lstnew(&obj, sizeof(t_stat)));
	else
		ft_lstadd(directorys_files, ft_lstnew(&obj, sizeof(t_stat)));

	return (EXIT_OK);
}


static void treat_file_list(t_options* options, t_list *list)
{
	if (!list)
		return;

	create_output_buffer(options, list);

	output_buffer(options, list);
}

static void treat_directory_list(t_options* options, t_list *list)
{
	if (!list)
		return;

	create_output_buffer(options, list);

	while (list) {
		handle_directory(options, list->content);

		list = list->next;
	}
}

/*
** Read the files arguments
** Got two lists :
** simple_files regoup all simples files that are not directorys
** directorys_files regroup all directorys file
**
** In fact, ls query first the simple and then the directorys
** when many arguments files are passed to command line
** @example
** ls Makefile src .gitignore /dev/sda .git
** will prompt something like
** /dev/sda  .gitignore  Makefile
**
** .git:
** ............. files in .git ........
**
** src:
** ............. files in src .........
**
** When many folder or files are set in the same command line arguments
** print the directory name of folders by setting the print_dir_name opt to 1
*/

int read_files_arguments(int ac, char **av, t_options *options)
{
	int					exit_value;
	int					i;
	t_list				*simple_files;
	t_list				*directorys_files;

	exit_value = EXIT_OK;

	simple_files = NULL;
	directorys_files = NULL;

	i = 1;
	while (i < ac)
	{
		if (!is_an_option(av[i])) {
			exit_value = fill_list_stats(options, av[i],
										&simple_files, &directorys_files);
		}
		i++;
	}

	if (!simple_files && !directorys_files && exit_value == EXIT_OK) {
		if ((exit_value = get_default_directory(options, &directorys_files, &simple_files)) != EXIT_OK)
			return (exit_value);
	}

	sort_file_list(options, &simple_files);
	sort_file_list(options, &directorys_files);

	treat_file_list(options, simple_files);

	if (ft_lstlen(directorys_files) > 1
		|| (simple_files && directorys_files))
		options->print_dir_name = 1;

	if (simple_files && directorys_files) {
		ft_putendl("");
	}

	treat_directory_list(options, directorys_files);

	ft_lstdel(&simple_files, &delete_file_node);
	ft_lstdel(&directorys_files, &delete_file_node);

	return (exit_value);
}
