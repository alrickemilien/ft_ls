#ifndef FT_LS_H
#define FT_LS_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>

#include "libft.h"

/*
** ERROR CODE
*/

/*
** All ok
*/

#define EXIT_OK 0

/*
** If minor problems (e.g., cannot access subdirectory)
*/

#define EXIT_MINOR_FAILURE 1

/*
** If serious trouble (e.g., cannot access command-line argument)
*/

#define EXIT_SERIOUS_FAILURE 2


/*
** Max number of displayed units by line when
** ls without option on a folder
*/

#define NUMBER_OF_FILE_ON_A_LINE 12

#define TARGET_OSX 1
#define TARGET_LINUX 2

/*
** #include <sys/acl.h> only on OSx because not native on Linux
** FT_LS_TARGET : Sets the target to TARGET_OSX or TARGET_LINUX value
** STAT_LAST_ACCESS : Define the name of the timespec struct in stat because diff between osx and linux
** STAT_LAST_MODIFICATION : Define the name of the timespec struct in stat because diff between osx and linux
*/

#ifdef __APPLE__
	#define FT_LS_TARGET 1

	#define LISTXATTR(path, buf, size) listxattr(path, buf, size, XATTR_NOFOLLOW)
	#define LLISTXATTR(path, buf, size) listxattr(path, buf, size, XATTR_NOFOLLOW)
	#define GETXATTR(path, buf, value, size) getxattr(path, buf, value, size, 0, XATTR_NOFOLLOW)
	#define LGETXATTR(path, buf, value, size) getxattr(path, buf, value, size, 0, XATTR_NOFOLLOW)
	#define STAT_LAST_ACCESS st_atimespec.tv_sec
	#define STAT_LAST_MODIFICATION st_mtimespec.tv_sec
	#define STAT_LAST_STATUS st_ctimespec.tv_sec

	#include <sys/acl.h>

	#define ERROR_NOT_A_DIRECTORY "ft_ls:"
#elif __linux__
	#define FT_LS_TARGET 2

	#define LISTXATTR(path, buf, size) listxattr(path, buf, size)
	#define LLISTXATTR(path, buf, size) llistxattr(path, buf, size)
	#define GETXATTR(path, buf, value, size) getxattr(path, buf, value, size)
	#define LGETXATTR(path, buf, value, size) lgetxattr(path, buf, value, size)

	#define STAT_LAST_ACCESS st_atim.tv_sec
	#define STAT_LAST_MODIFICATION st_mtim.tv_sec
	#define STAT_LAST_STATUS st_ctimc.tv_sec

	#define ERROR_NOT_A_DIRECTORY ":ft_ls: cannot open directory"
#endif


/*
** EXTENDED ATTRIBUTES and ACL
*/

#define EXTENDED_ATTRIBUTE_CHARACTER "@"
#define ACL_CHARACTER "+"

# define NUMBER_OF_S_IN_ONE_YEAR 31536000
# define NUMBER_OF_S_IN_A_MONTH 2629746

#include "ft_ls_options.h"

/*
** !! WARNING !! order matters
** struct stat stat must stay FIRST
** Structure of a file
** - Stats on the file
** - A filename
** - color_buffsize: in order to remove color char
** when column calculating buffer
*/

typedef struct	s_stat {
	struct stat		stat;
	char					*path;
	char					*name;
	char 					*buffer;
	int 					color_buffsize;
	char					*listxattr;
	ssize_t 			listxattr_size;

	#ifdef __APPLE__
		acl_t					acl;
	#endif

	struct s_stat	*link;
}								t_stat;


/*
** This macro is used to have
** a cleaner access to stats of t_stat structure
*/

#define ACCESS_STATS(x) ((struct stat *)(x))

/*
** This macro is used to have
** a cleaner access to link stats
** in t_stat structure
*/

#define ACCESS_LINK_STATS(x) ((struct stat *)(x)->link)

/*
** Main cmd parsing functions
*/

int read_options_arguments(int ac, char **av, t_options *opt);
int read_files_arguments(int ac, char **av, t_options *opt);

/*
** Files stat functions
*/

char *get_file_permissions(t_options *options, struct stat *p);
char *get_file_user_id(t_options *options, struct stat *p);
char *get_file_group_id(t_options *options, struct stat *p);
char *get_file_size(t_options *options, struct stat *p);
char *get_file_link_number(t_options *options, struct stat *p);
char *get_file_last_access_date(t_options *options, struct stat *p);
char *get_file_type(t_options *options, struct stat *p);
char *get_file_path(t_options *options, struct stat *p);
char *get_file_extended_attributes(t_options *options, struct stat *p);
char *get_file_inode(t_options *options, struct stat *p);
char *get_file_access_control(t_options *options, struct stat *p);
char *get_file_acl(t_options *options, struct stat *p);
char *get_file_icone(t_options *options, struct stat *file);
char *list_file_acl(t_options *options, struct stat *p);
void list_file_xattr(t_options *options, struct stat *p);

/*
** File hanlder according to it mode
*/

int handle_regular_file(t_options *options, t_stat *p);
int handle_directory(t_options *options, t_stat *p);

/*
** Display / buffer
*/

void create_output_buffer(t_options *options, t_list *list);
void output_buffer(t_options *options, t_list *list);
void columns_display(t_options *options, t_list *list);

/*
** Sort functions
*/

void sort_file_list(t_options *options, t_list **list);
int sort_by_filename(void *a, void *b);
int sort_by_filename_reverse(void *a, void *b);
int sort_by_creation_date_and_alpha(void *a, void *b);
int sort_by_last_modification_and_alpha(void *a, void *b);
int sort_by_file_size(void *a, void *b);

/*
** Utils
*/

void print_error_on_file(const char *error_msg, const char *name);
void print_error_on_option(const char *error_msg, const char *name);
char *path_from_dir(const char *dirname, const char *filename);
int is_dot_file(const char *name);
int is_dot_directory(const char *name);
char *get_link_path(char *path_of_link);
void delete_file_node(void *ptr, size_t size);
int is_an_option(const char *name);
char *get_filename_from_path(char *path);
int end_with_slash(const char * str);
void delete_file_link(t_stat *link);

/*
** LS Utils
*/

int read_link_stat(t_stat  *file, bool do_fail);
int read_file_stat(t_stat *file);

#endif
