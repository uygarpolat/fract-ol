# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/28 02:21:29 by upolat            #+#    #+#              #
#    Updated: 2024/08/02 03:14:52 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
CC := cc
CFLAGS := -Wall -Wextra -Werror -Ofast -flto
LIBMLX := ./lib/MLX42

HEADERS := -I ./include -I $(LIBMLX)/include -I /opt/homebrew/Cellar/glfw/3.4/include
LIBS := ${LIBMLX}/build/libmlx42.a -ldl -lglfw -pthread -lm

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
	$(CC) $(MANDATORY_OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME)-bonus: $(BONUS_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(NAME)

.mandatory: $(MANDATORY_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(MANDATORY_OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@touch .mandatory
	@rm -f .bonus

.bonus: $(BONUS_OBJS) $(LIBMLX)/build/libmlx42.a
	$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@touch .bonus
	@rm -f .mandatory

$(LIBMLX)/build/libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	rm -rf $(MANDATORY_OBJS) $(BONUS_OBJS)
	rm -rf $(LIBMLX)/build
	@rm -f .bonus .mandatory

fclean: clean
	rm -rf $(NAME)
	@rm -f .bonus .mandatory

re: fclean all

.PHONY: all clean fclean re libmlx mandatory bonus
