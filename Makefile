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
CFLAGS		=	$(INCLUDES) $(DEBUG)
WFLAGS		=	-Wall -Werror -Wextra
INCLUDES	=	-I$(INC_LIBFT) -I$(INC_DIR) -I$(MLX_DIR) $(FSAN)
DEBUG		=	-g3
FSAN		=	-fsanitize=address,leak
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


LIB_FLAGS		=	-L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRCS_FILES		=	srcs/debug.c \
					srcs/error.c \
					srcs/main.c \
					srcs/free.c \
					srcs/parse/parse.c \
					srcs/parse/parse_map.c \
					srcs/parse/parse_map_utils.c \
					srcs/parse/check_valid_map.c \
					srcs/parse/check_valid_map2.c \
					srcs/parse/check_valid_map_utils.c \
					srcs/parse/parse_texture.c \
					srcs/parse/parse_texture_utils.c \
					srcs/utils.c \
					srcs/utils_cleanup.c \
					srcs/exec/init.c \
					srcs/exec/raycasting.c \
					srcs/exec/textures.c \
					srcs/exec/dda.c \
					srcs/exec/draw_floor_ceiling.c \
					srcs/exec/minimap.c \
					srcs/exec/utils_minimap.c \
					srcs/mlx/utils_colour.c \
					srcs/mlx/mlx.c \
					srcs/mlx/hooks_movement.c \
					srcs/mlx/hooks_movement_calc.c \
					srcs/mlx/hooks_mouse.c

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
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INC_DIR)cub3d.h | $(OBJS_DIR)
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
