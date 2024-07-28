# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 02:21:29 by upolat            #+#    #+#              #
#    Updated: 2024/07/28 02:21:31 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42

# HEADERS	:= -I ./include -I $(LIBMLX)/include
# LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
# HEADERS := -I ./include -I $(LIBMLX)/include -I /opt/homebrew/Cellar/glfw/3.4/include
# LIBS := $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -ldl -pthread -lm
HEADERS := -I ./include -I $(LIBMLX)/include -I /opt/homebrew/Cellar/glfw/3.4/include
LIBS := $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
