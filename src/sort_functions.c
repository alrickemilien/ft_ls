#include "ft_ls.h"

/*
** Sort functions
*/

int sort_by_filename(void *a, void *b)
{
  if ((FT_LS_TARGET != TARGET_OSX))
    return (ft_strcmp_alpha(((t_stat*)a)->name, ((t_stat*)b)->name));
  return (ft_strcmp(((t_stat*)a)->name, ((t_stat*)b)->name));
}

int sort_by_filename_reverse(void *a, void *b)
{
    return (ft_strcmp_alpha(((t_stat*)b)->name, ((t_stat*)a)->name));
}

int sort_by_creation_date_and_alpha(void *a, void *b)
{
  int cmp;

  cmp = (int)(((struct stat *)b)->STAT_LAST_ACCESS - ((struct stat *)a)->STAT_LAST_ACCESS);

  if (cmp == 0)
    return (ft_strcmp(((t_stat*)a)->name, ((t_stat*)b)->name));

  return (cmp);
}

int sort_by_last_modification_and_alpha(void *a, void *b)
{
    int cmp;

    cmp = (int)(((struct stat *)b)->STAT_LAST_MODIFICATION - ((struct stat *)a)->STAT_LAST_MODIFICATION);

    if (cmp == 0)
      return (ft_strcmp(((t_stat*)a)->name, ((t_stat*)b)->name));

    return (cmp);
}

int sort_by_file_size(void *a, void *b)
{
    return ((int)(((struct stat *)b)->st_size - ((struct stat *)a)->st_size));
}
