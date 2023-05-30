# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 10:27:35 by anmassy           #+#    #+#              #
#    Updated: 2023/05/29 11:21:25 by anmassy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC =	srcs/check.c \
		srcs/utils.c \
		srcs/init.c \
		srcs/routine.c \
		srcs/philo.c

OBJ = $(SRC:.c=.o)

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
INCS = -I ./include

GREY = \e[0;30m
RED = \e[0;31m
GREEN = \e[0;32m

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME)

clean :
	@echo "$(RED) Cleaning files..."
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean : clean
	@echo -n "$(RED)"
	@echo " Cleaning binaries..."
	@$(RM) $(NAME)

re : fclean all
	@echo "$(GREEN) re-make finish"

.PHONY : all clean fclean re
