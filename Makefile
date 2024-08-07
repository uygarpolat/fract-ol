# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 02:21:29 by upolat            #+#    #+#              #
#    Updated: 2024/08/07 12:55:15 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
CC := clang
CFLAGS := -Wall -Wextra -Werror -Ofast -flto -fno-builtin
LDFLAGS := -flto
LIB_DIR := ./lib
LIBMLX := $(LIB_DIR)/MLX42
MLX42_REPO := https://github.com/codam-coding-college/MLX42.git

# Linux
HEADERS := -I ./include -I $(LIBMLX)/include -I /usr/include
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

#MacOS
# HEADERS := -I ./include -I $(LIBMLX)/include -I /opt/homebrew/Cellar/glfw/3.4/include
# LIBS := $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

MANDATORY_SRCS := src/mandatory/arithmetic.c \
                  src/mandatory/colors.c \
                  src/mandatory/fractol.c \
                  src/mandatory/hooks.c \
                  src/mandatory/sets.c \
                  src/mandatory/utils.c \
                  src/mandatory/validity.c

BONUS_SRCS := src/bonus/arithmetic_bonus.c \
              src/bonus/colors_bonus.c \
              src/bonus/fractol_bonus.c \
              src/bonus/hooks_bonus.c \
              src/bonus/sets_bonus.c \
              src/bonus/utils_bonus.c \
              src/bonus/validity_bonus.c

MANDATORY_OBJS := $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

all: mandatory

mandatory: .mandatory

bonus: .bonus

$(NAME): $(MANDATORY_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(MANDATORY_OBJS) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME)

$(NAME)-bonus: $(BONUS_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME)

.mandatory: $(MANDATORY_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(MANDATORY_OBJS) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME)
	@touch .mandatory
	@rm -f .bonus

.bonus: $(BONUS_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME)
	@touch .bonus
	@rm -f .mandatory

$(LIBMLX)/build/libmlx42.a: $(LIBMLX)
	@cd $(LIBMLX) && cmake -B build
	@make -C $(LIBMLX)/build -j4

$(LIBMLX):
	@if [ ! -d $(LIBMLX) ]; then \
		echo "Cloning MLX42 library..."; \
		mkdir -p $(LIB_DIR); \
		cd $(LIB_DIR) && git clone $(MLX42_REPO); \
	fi

%.o: %.c $(LIBMLX)/build/libmlx42.a
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@file $@

clean:
	rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)
	@rm -f .bonus .mandatory

fclean: clean
	rm -rf $(NAME)
	@rm -f .bonus .mandatory

re: fclean all

.PHONY: all clean fclean re libmlx mandatory bonus
