#include "ft_ls.h"

char *list_file_acl(t_options *options, struct stat *p)
{
  acl_entry_t entry;
  int entryId;
  int i;
  char *text;

  (void)options;

  if (!((t_stat*)p)->acl)
    return (NULL);

  entryId = ACL_FIRST_ENTRY;

  while (42) {
    if (acl_get_entry(((t_stat*)p)->acl, entryId, &entry) == -1)
      break;

     ssize_t ptr[1];

     (void)ptr;

     ft_putstr(" ");
     ft_putstr(ft_itoa(entryId));

     ft_putstr(": ");

     text = acl_to_text(((t_stat*)p)->acl, ptr);

     i = 0;
     while (text[i] && text[i] != '\n')
       i++;

	recycle(&text, ft_strtrim(text + i + 1));

    ft_putendl(text);

    free(text);

    entryId = ACL_NEXT_ENTRY;
  }

  if (acl_free(((t_stat*)p)->acl) == -1)
      return (NULL);

  ((t_stat*)p)->acl = NULL;

  return ((void*)1);
}

/*
** Read file ACLs
*/

char *get_file_acl(t_options *options, struct stat *p)
{
    acl_t acl;
    acl_type_t type;

    (void)options;

    type = ACL_TYPE_EXTENDED;

    acl = acl_get_file(((t_stat*)p)->path, type);

    if (acl == NULL)
        return (NULL);

    ((t_stat*)p)->acl = acl;

    return (ft_strdup(ACL_CHARACTER));
}
