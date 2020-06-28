CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -D BUFFER_SIZE=10
LIBS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
MLX = libmlx.a

SRCS = ./cub3d_parse/bmp.c ./cub3d_parse/check_exception.c ./cub3d_parse/color.c\
	./cub3d_parse/cub3d.c ./cub3d_parse/exit.c ./cub3d_parse/init.c\
	./cub3d_parse/map2.c ./cub3d_parse/parse_map_tex.c\
	./cub3d_parse/parse_map.c ./cub3d_parse/parser.c ./cub3d_parse/player.c\
	./cub3d_parse/sprite.c ./cub3d_parse/util.c\
	./cub3d_raycasting/floorCeiling.c ./cub3d_raycasting/key_event.c\
	./cub3d_raycasting/move.c ./cub3d_raycasting/sprite.c\
	./cub3d_raycasting/sprite2.c ./cub3d_raycasting/wall.c\
	./cub3d_raycasting/wall2.c\
	./gnl/get_next_line.c ./gnl/get_next_line_utils.c

OBJS = $(SRCS:%.c=%.o)

NAME = cub3d

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS) cub3d.h ./gnl/get_next_line.h
	@make -C libft
	@make -C minilibx
	cp minilibx/$(MLX) ./
	cp libft/libft.a ./
	$(CC) $(SRCS) libft.a $(MLX) $(CFLAGS) -o $(NAME) $(LIBS)

clean :
	cd ./libft; make clean
	cd ./minilibx; make clean
	rm -f $(OBJS)

fclean :
	cd ./libft; make fclean
	cd ./minilibx; make clean
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f libft.a

norm :
	norminette -R CheckForbiddenSourceHeader ./.c ./.h

re : fclean all
