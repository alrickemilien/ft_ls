#include "ft_ls.h"
#include "color.h"

/*
** The struicture of stat file contains the following infos
** concerning dates :
**
** struct timespec st_atim;  // time of last access
** struct timespec st_mtim;  // time of last modification
** struct timespec st_ctim;  // time of last status change
**
** The structure timespec is like this :
** time_t  tv_sec    seconds
** long    tv_nsec   nanoseconds
*/

/*
** Use the return of ctime + 4
** because ctime return a string like
** Wed Jul 25 11:10:06 2018
** With the first word a day of the week that
** always is 3 characters length
** We add 4 to skip the 3 characters + the space
**
** Soubstract 13 char because we want avoid the
** :06 2018 part of
** Wed Jul 25 11:10:06 2018
**
*/

static char *get_formated_file_last_access_date(time_t current_time, char *ctime_str, struct stat *p)
{
	char *ret;
	char *ptr_on_hour;
	char *ptr_on_year;
	size_t i;

	ret = ft_strdup(ctime_str + 4);

	if (current_time - p->STAT_LAST_MODIFICATION > NUMBER_OF_S_IN_A_MONTH * 6
		|| current_time - p->STAT_LAST_MODIFICATION < NUMBER_OF_S_IN_A_MONTH * -6)
	{
		ptr_on_hour = ft_strchr(ret, ':') - 2;

		ptr_on_year = ft_strchr(ctime_str, ':') + 7;

		*(ptr_on_year + 4) = 0;

		i = 0;
		while (5 - i > ft_strlen(ptr_on_year))
		{
			ptr_on_hour[i] = ' ';
			i++;
		}

		ft_memcpy(ptr_on_hour + i, ptr_on_year, ft_strlen(ptr_on_year));
		ret[ft_strlen(ctime_str) - 12] = 0;
	} else {
		ret[ft_strlen(ctime_str) - 13] = 0;
	}

	return (ret);
}



/*
** Get the date of the last access of the file
** - Ubuntu : print last access
** - OSX : print last modification
*/

char *get_file_last_access_date(t_options *options, struct stat *p) {
	time_t current_time;

	if ((current_time = time(NULL)) == (time_t) - 1)
		return (NULL);

	if (!options->listing)
		return ft_strdup("");

	if ((p->st_mode & S_IFMT ) == S_IFLNK) {
		return get_formated_file_last_access_date(current_time, ctime(& p->STAT_LAST_MODIFICATION), p);
  }

	if (FT_LS_TARGET == TARGET_OSX)
		return get_formated_file_last_access_date(current_time, ctime(& p->STAT_LAST_MODIFICATION), p);

	return get_formated_file_last_access_date(current_time, ctime(& p->STAT_LAST_ACCESS), p);
}
