#include "ft_ls.h"

/*
** This function returns a buffer with the user id as string
** When no user name has been matched with st_uid,
** print directly the int value of st_uid
*/

char *get_file_user_id(t_options *options, struct stat *p) {
	struct passwd	*passwd;

	if (!options->listing || options->do_not_print_owner)
		return ft_strdup("");

  if ((passwd = getpwuid(p->st_uid)) == NULL) {
    return (ft_itoa((int)p->st_uid));
  }

  return (ft_strdup(passwd->pw_name));
}

/*
** This function returns a buffer with the user id as string
** When no group name has been matched with st_gid,
** print directly the int value of st_gid
*/

char *get_file_group_id(t_options *options, struct stat *p) {
  struct group  *group;

	if (!options->listing)
		return ft_strdup("");

  if ((group = getgrgid(p->st_gid)) == NULL) {
    return (ft_itoa((int)p->st_gid));
  }

  return (ft_strdup(group->gr_name));
}
