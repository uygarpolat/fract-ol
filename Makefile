# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 02:21:29 by upolat            #+#    #+#              #
#    Updated: 2024/08/02 02:30:09 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
CC := cc
CFLAGS := -Wall -Wextra -Werror -Ofast -flto
LIBMLX := ./lib/MLX42

HEADERS := -I ./include -I $(LIBMLX)/include -I /opt/homebrew/Cellar/glfw/3.4/include
LIBS := $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

MANDATORY_SRCS := $(wildcard src/mandatory/*.c)
BONUS_SRCS := $(wildcard src/bonus/*.c)

MANDATORY_OBJS := $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

all: $(NAME)

mandatory: $(NAME)

bonus: $(NAME)-bonus

$(NAME): libmlx $(MANDATORY_OBJS)
	$(CC) $(MANDATORY_OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME)-bonus: libmlx $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME) $(NAME)-bonus

re: fclean all

.PHONY: all clean fclean re libmlx mandatory bonus

