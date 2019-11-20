#include "ft_ls.h"
#include "emoji.h"

static const t_icone map[8] = {
    {
     "Dockerfile",
      EMOJI_WHALE,
    },
      {
    ".git",
      EMOJI_GIT,
    },
      {
    ".c",
      EMOJI_GIT,
    },
      {
    ".jsx",
      EMOJI_JSX,
    },
      {
    ".java",
      EMOJI_JAVA,
    },
      {
    ".js",
      EMOJI_JAVASCRIPT,
    },
      {
    ".go",
      EMOJI_GO,
    },
      {
    ".xlsx",
      EMOJI_EXCEL,
    },
};

/*
** Prints emoji
*/

char *get_file_icone(t_options *options, struct stat *file)
{
  char* emoji;
  int i;

  if (!options->emoji)
    return (ft_strdup(""));

  emoji = EMOJI_DEFAULT;

  i = 0;
  while (i < 8)
  {
    if(string_end_with(((t_stat*)file)->path, map[i].extension)) {
      emoji = map[i].value;
      break;
    }
    i++;
  }

  return ft_strdup(emoji);
}
