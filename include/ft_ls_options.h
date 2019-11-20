#ifndef READ_ARGS_H
#define READ_ARGS_H

/**
** Number of handled parameters
*/

#define OPTIONS_MAP_LENGTH 21

enum {
	LISTING_OPTION,
	RECURSIVE_OPTION,
	ALL_OPTION,
	REVERSE_OPTION,
	SORT_MODIFICATION_TIME_OPTION,
	PRINT_DIR_NAME,
	INODE_OPTION,
	COLOR_OPTION,
	SIMPLE_LISTING,
	SORT_BY_FILE_SIZE,
	DO_NOT_PRINT_OWNER,
	COMMA,
	ONLY_DIRECTORY,
	DO_NOT_SORT,
	ACL,
	XATTR,
	EMOJI,
};


/*
** Map used to handle each option :
** name : Char* value
** offset: offset in the structure s_options
*/

typedef struct 	s_options_map {
	char		*name;
	int			offset;
}				t_options_map;

/*
** Structure filled with options passed to program
** The handled options are currently -l, -R, -a, -r et -t
** None ls option used in the code :
** print_dir_name : print the dir name in some case at top of list
** At the end stor tty infos
** !! WARNING !!
** Options in struct s_options must be in the same order
** that the enum
*/

typedef struct s_options {
	int listing;
	int recursive;
	int all;
	int reverse;
	int sort_by_modif_time;
	int print_dir_name;
	int inode;
	int color;
	int simple_listing;
	int sort_by_file_size;
	int do_not_print_owner;
	int comma;
	int only_directory;
	int do_not_sort;
	int acl;
	int xattr;
	int emoji;

	int is_tty;
	struct winsize win;
} t_options;

#endif
