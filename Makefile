#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

.PHONY: all clean fclean re
# .SILENT:

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# add back WFLAGS later to CFLAGS, removed cause it doesnt work for testing
# Compiler and flags
CC			=	clang
CFLAGS		=	$(INCLUDES) $(DEBUG) $(FSAN)
WFLAGS		=	-Wall -Werror -Wextra
INCLUDES	=	-I$(INC_LIBFT) -I$(INC_DIR) -I$(MLX_DIR)
DEBUG		=	-g3
FSAN		=	-fsanitize=address,leak -g3
RM			=	rm -rf

# Output file name
NAME	=	cub3D

# Directories
LIBFT_DIR		=	libft/
INC_LIBFT		=	libft/includes
INC_DIR			=	includes/
MLX_DIR			=	minilibx-linux/


SRCS_DIR		=	srcs/
OBJS_DIR		=	bin/


LIB_FLAGS		=	-L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz $(FSAN)


SRCS_FILES		=	srcs/debug.c \
					srcs/error.c \
					srcs/main.c \
					srcs/parse.c \
					srcs/utils.c \
					srcs/mlx/mlx_colour_utils.c \
					srcs/mlx/mlx.c

OBJS_FILES		=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS_FILES))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

# Generates output file
$(NAME): $(OBJS_FILES)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_FILES) -o $(NAME) $(LIB_FLAGS)

# Rule to compile the object files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the object directory if it doesn't exist
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

remake_libft:
	make re -C $(LIBFT_DIR)

# Removes objects
clean:
	$(RM) $(OBJS_DIR)

# Removes objects and executables
fclean: clean
	$(RM) $(NAME)
	make clean -C $(MLX_DIR)
	make fclean -C $(LIBFT_DIR)

# Removes objects and executables and remakes
re: fclean $(OBJS_DIR) all
