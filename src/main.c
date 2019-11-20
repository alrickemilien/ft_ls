#include "ft_ls.h"

/*
** - Sets the options according too tty settings
*/

static void	set_tty_options(t_options *options)
{
	options->is_tty = isatty(1);

	if (options->simple_listing)
		options->listing = 0;

	if (!options->simple_listing)
		options->simple_listing = !options->is_tty;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &options->win);
}

/*
** - Read options from command line
** - Sets the options according too tty settings
** - Read files and directorys from command line
*/

int	main(int ac, char **av)
{
	t_options	options;

	if (read_options_arguments(ac, av, &options) == EXIT_MINOR_FAILURE)
		return (EXIT_MINOR_FAILURE);

	set_tty_options(&options);

	return read_files_arguments(ac, av, &options);
}
