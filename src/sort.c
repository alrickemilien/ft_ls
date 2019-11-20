#include "ft_ls.h"

/*
** The main function for quick sort. This is a wrapper over recursive
** function quickSortRecur()
*/

static void sort(t_list **list, int (*sort)(void*, void*))
{
    (*list) = quick_sort_list(*list, sort);

    return;
}

/*
** ./ft_ls -l ==> alphanum only
** ./ft_ls -l -r ==> alphanum only and then reverse
** ./ft_ls -l -r -t ==> alphanum only and then reverse
*/

void sort_file_list(t_options *options, t_list **list)
{
  if (options->do_not_sort)
    return ft_lstreverse(list);

  // Size have priority
  if (options->sort_by_file_size) {
    sort(list, sort_by_file_size);

    if (options->reverse) {
      ft_lstreverse(list);
    }

    return ;
  }

  // ./ft_ls -l -t ==> time
  if (options->sort_by_modif_time) {
    if ((FT_LS_TARGET != TARGET_OSX))
      sort(list, sort_by_creation_date_and_alpha);
    else
      sort(list, sort_by_last_modification_and_alpha);

    // ./ft_ls -l -r -t ==> then reverse
    if (options->reverse) {
      ft_lstreverse(list);
    }

    return ;
  }

  // ./ft_ls -1 -r
  if (options->reverse) {
    sort(list, sort_by_filename);
    ft_lstreverse(list);
  } else {
    // ./ft_ls -1
    sort(list, sort_by_filename);
  }

}
