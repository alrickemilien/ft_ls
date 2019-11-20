#include "ft_ls.h"
#include "color.h"

/*
** Initialize here the functions that return stat on each part of ls -l format
*/

static char* (* const format_functions[11])(t_options *, struct stat *) = {
	&get_file_inode,
	&get_file_type,
	&get_file_permissions,
	&get_file_link_number,
	&get_file_user_id,
	&get_file_group_id,
	&get_file_size,
	&get_file_last_access_date,
	&get_file_icone,
	&get_file_path,
	NULL,
};

/*
** Format_functions
** for which we need to append a space to the returned string
*/
static char* (* const format_functions_to_append_space_to_return_value[9])(t_options *, struct stat *) = {
	&get_file_inode,
	&get_file_permissions,
	&get_file_link_number,
	&get_file_user_id,
	&get_file_group_id,
	&get_file_size,
	&get_file_last_access_date,
	&get_file_icone,
	NULL,
};

static void append_space_to_return(
	char **buffer,
	char * (* const function)(t_options *, struct stat *))
{
	int i;

	i = 0;
	while (format_functions_to_append_space_to_return_value[i])
	{
		if (format_functions_to_append_space_to_return_value[i] == function) {
			recycle(buffer, ft_strjoin(*buffer, " "));
			return ;
		}
		i++;
	}
}

static int fill_array_and_get_biggest_string(
	t_options *options,
	t_list *x,
	char **tmp,
	char* (* const get_string)(t_options *, struct stat *))
{
	size_t j;
	int biggest_string;
	int temporary_length;

	biggest_string = 0;
	j = 0;
	while (x) {
		tmp[j] = get_string(options, (struct stat *) x->content);

		if (!tmp[j]) {
			ft_putendl("Serious fail");
			exit(EXIT_SERIOUS_FAILURE);
		}

		temporary_length = (int)ft_strlen(tmp[j]);

		if (biggest_string < temporary_length)
			biggest_string = temporary_length;

		x = x->next;

		j++;
	}

	return (biggest_string);
}

/*
** Creates an output buffer
** Loop over each function of the format format
** @example
** This is an, outpout of ls -li
** 158541 drwxr-xr-x+ 147 root root 12288 sept. 12 06:02 etc
** The format_functions array have a function for each of the following block :
** 158541 (inode)
** d (file type)
** rwxr-xr-x (rights)
** + (xattr or acl)
** 147 (size block)
** root (user)
** ...
** etc -> private/etc (path)
** Following variables :
** - tmp stores for each block the biggest string in biggest_string
** among each listed file or directory
** - i is used to loop over static array format_functions
** - j is used to loop over tmp and is the index of the node in the t_list
** - x is used to loop over list
*/

void create_output_buffer(t_options *options, t_list *list)
{
	size_t i;
	size_t j;
	char **tmp;
	t_list *x;
	int biggest_string;

	tmp = (char**)malloc(sizeof(char*) * ft_lstlen(list));

	i = 0;
	while (format_functions[i]) {
		biggest_string = fill_array_and_get_biggest_string(options, list, tmp, format_functions[i]);

		x = list;
		j = 0;
		while (x) {
			if (options->listing && i != 2 && i != 5 && format_functions[i + 1]) {
				preppend_n_space_to_string(&tmp[j],
					(int)biggest_string - ft_strlen(tmp[j]));
			}
			else if (options->listing && format_functions[i + 1]) {
				append_n_space_to_string(&tmp[j],
					(int)biggest_string - ft_strlen(tmp[j]));
			}

			if (!((t_stat *) x->content)->buffer)
				((t_stat *) x->content)->buffer = ft_strdup(tmp[j]);
			else
				recycle(&((t_stat *) x->content)->buffer, ft_strjoin(((t_stat *) x->content)->buffer, tmp[j]));


			if (options->listing && tmp[j][0])
				append_space_to_return(&((t_stat *) x->content)->buffer, format_functions[i]);

			free(tmp[j]);

			j++;
			x = x->next;
		}

		i++;
	}

	free(tmp);
}
