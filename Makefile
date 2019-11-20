CCFLAGS= -Wall -Wextra -Werror

OS=$(shell uname)

LIBFT=libft
DIR_LIBFT=libft
LINK_LIBFT=-lft -L $(DIR_LIBFT)

LS=ft_ls
SRC=src/main.c \
	src/read_options_arguments.c \
	src/read_files_arguments.c \
	src/file_handlers.c \
	src/file_permission.c \
	src/file_ids.c \
	src/file_size.c \
	src/file_links.c \
	src/file_time_stat.c \
	src/file_type.c \
	src/file_path.c \
	src/file_extended_attributes.c \
	src/file_inode.c \
	src/file_icone.c \
	src/utils.c \
	src/sort.c \
	src/sort_functions.c \
	src/output_in_column.c \
	src/create_output_buffer.c \
	src/ls_utils.c \

ifeq ($(OS),Darwin)
	SRC += src/file_acl.c
endif


OBJ=$(SRC:.c=.o)

INCLUDE=-I include -I libft

.PHONY: all clean fclean

all: $(LS)

$(LS): $(OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -o $@ $(LINK_LIBFT) $(CCFLAGS)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf $(LS)

re: fclean all
