# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:11:30 by jmakkone          #+#    #+#              #
#    Updated: 2024/10/08 09:41:44 by mpellegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = philo
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM              = rm -f
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -I$(INC_DIR) -pthread

all:	$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
