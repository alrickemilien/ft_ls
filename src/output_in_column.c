#include "ft_ls.h"
#include "color.h"

/*
**
*/

static void print_list_in_column(t_options *options, t_list *list, size_t jump, int nb_columns, int *columns)
{
  t_list *tmp_x;
  t_list *tmp_y;
  int c;
  size_t j;
  size_t i;

  tmp_x = list;
  j = 0;
  while (j < jump && tmp_x) {
    tmp_y = tmp_x;

    c = 0;
    while (tmp_y) {
      ft_putstr(((t_stat*)(tmp_y->content))->buffer);

      if (c < nb_columns) {
        i = 0;
        while (!options->comma && i < (columns[c]
          - ft_strlen(((t_stat*)(tmp_y->content))->buffer)
          + ((t_stat*)(tmp_y->content))->color_buffsize
        )) {
          ft_putstr(" ");
          i++;
        }
        if (options->comma)
          ft_putstr(", ");
        else
          ft_putstr("  ");
      }

      i = 0;
      while (i < jump && tmp_y) {
        i++;
        tmp_y = tmp_y->next;
      }

      c++;
    }

    j++;

    ft_putendl("");
    tmp_x = tmp_x->next;
  }
}

/*
** Without -l option, l displays the files as columns
*/

static int jump_and_get_biggest_string_size(t_list **lst, size_t jump)
{

	size_t biggest_string_len;
	size_t i;
  size_t tmp;

	i = 0;
	biggest_string_len = 0;
	while (i < jump && *lst) {
    tmp = ft_strlen(((t_stat*)((*lst)->content))->buffer)  - ((t_stat*)((*lst)->content))->color_buffsize;
		// Determiner la biggest string pour chaque colonne
		if (biggest_string_len < tmp)
			biggest_string_len = tmp;

		i++;

		*lst = (*lst)->next;
	}


	return (int)(biggest_string_len);
}

void columns_display(t_options *options, t_list *list)
{
	t_list *tmp_x;
	int len;
	int jump;
	int *columns_biggest_string_length;
	int c;
  int ret;

	// ///////////////////////////////////////////////////////////////////
	// Check if all can be written on a row
	// ///////////////////////////////////////////////////////////////////

	len = 0;
	tmp_x = list;
	while (tmp_x) {
		len += ft_strlen(((t_stat*)(tmp_x->content))->buffer) - ((t_stat*)(tmp_x->content))->color_buffsize + 2;

		if (len > (int)options->win.ws_col)
			break;
		tmp_x = tmp_x->next;
	}

	if (len < (int)options->win.ws_col) {
		tmp_x = list;
		while (tmp_x) {
			ft_putstr(((t_stat*)(tmp_x->content))->buffer);

      if (tmp_x->next && options->comma)
        ft_putstr(", ");
      else if (tmp_x->next)
				ft_putstr("  ");

			tmp_x = tmp_x->next;
		}
    ft_putendl("");

		return;
	}

	// ///////////////////////////////////////////////////////////////////
	// When all cannot be written on a row
	// ///////////////////////////////////////////////////////////////////

	// jump --> nb de row
	jump = 1;

	columns_biggest_string_length = (int*)malloc(sizeof(int) * (int)(ft_lstlen(list)));
	ft_bzero(columns_biggest_string_length, sizeof(int) * (int)(ft_lstlen(list)));

	len = 0;
	c = 0;

  tmp_x = list;
  // For each column
	while (tmp_x) {
		// jump to i eme next node of the list
		// Determiner la biggest string pour chaque colonne

    ret = jump_and_get_biggest_string_size(&tmp_x, jump);

    if (!columns_biggest_string_length[c])
      columns_biggest_string_length[c] = ret;

		len += columns_biggest_string_length[c] + 2;

		// When (int)options->win.ws_col is reached, reset with an added row
		if (len > (int)options->win.ws_col) {
			len = 0;
			c = 0;
			tmp_x = list;
			jump++;
			ft_bzero(columns_biggest_string_length, sizeof(int) * (int)(ft_lstlen(list)));
		} else {
      c++;
    }
	}

  print_list_in_column(options, list, jump, c - 1, columns_biggest_string_length);

  free(columns_biggest_string_length);
}
