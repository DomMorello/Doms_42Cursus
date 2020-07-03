CC = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=10
MLXFLAGS = -lm -lmlx -framework OpenGL -framework AppKit
MLX = libmlx.a
LIBFT = libft.a

SRCS = ./cub3d_parse/bmp.c ./cub3d_parse/check_exception.c ./cub3d_parse/color.c\
	./cub3d_parse/cub3d.c ./cub3d_parse/exit.c ./cub3d_parse/init.c\
	./cub3d_parse/map2.c ./cub3d_parse/parse_map_tex.c\
	./cub3d_parse/parse_map.c ./cub3d_parse/parser.c ./cub3d_parse/player.c\
	./cub3d_parse/sprite.c ./cub3d_parse/util.c\
	./cub3d_raycasting/floor_ceiling.c ./cub3d_raycasting/key_event.c\
	./cub3d_raycasting/move.c ./cub3d_raycasting/sprite.c\
	./cub3d_raycasting/sprite2.c ./cub3d_raycasting/wall.c\
	./cub3d_raycasting/wall2.c\
	./gnl/get_next_line.c ./gnl/get_next_line_utils.c

OBJS = $(SRCS:%.c=%.o)

NAME = cub3d

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@make -C mlx
	cp mlx/$(MLX) ./
	cp libft/$(LIBFT) ./
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

clean :
	cd ./libft; make clean
	cd ./mlx; make clean
	rm -f $(OBJS)

fclean :
	cd ./libft; make fclean
	cd ./mlx; make clean
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(MLX)

norm :
	norminette -R CheckForbiddenSourceHeader ./.c ./.h

re : fclean all
