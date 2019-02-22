# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 15:21:27 by gbiebuyc          #+#    #+#              #
#    Updated: 2019/02/22 19:14:35 by nallani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRC = src/main.c \
	  src/hooks.c \
	  src/vec2.c \
	  src/image.c
OBJ = $(SRC:.c=.o)
FT_DIR = libft
# On Ubuntu, install libxext-dev package beforehand.
ifeq ($(shell uname), Linux)
	MLX_DIR = minilibx_linux
	LDFLAGS = -lm -L $(FT_DIR) -lft -L $(MLX_DIR) -lmlx -lXext -lX11
else
	MLX_DIR = minilibx_macos
	LDFLAGS = -lm -L $(FT_DIR) -lft -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
CFLAGS = -I $(FT_DIR) -I $(MLX_DIR) -Wall -Wextra -Werror
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(FT_DIR)
	make -C $(MLX_DIR)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	make -C $(FT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -rf $(OBJ)

fclean:
	make -C $(FT_DIR) fclean
	make -C $(MLX_DIR) clean
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all
