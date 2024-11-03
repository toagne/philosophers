# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: giuls <giuls@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 09:05:38 by mpellegr          #+#    #+#              #
#    Updated: 2024/11/03 15:56:16 by giuls            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = philo
SRC_DIR         = src
INC_DIR         = inc

SRC             = $(SRC_DIR)/main.c $(SRC_DIR)/routine.c $(SRC_DIR)/create_table.c $(SRC_DIR)/utils.c \
					$(SRC_DIR)/init_data.c $(SRC_DIR)/monitor_routine.c \
					$(SRC_DIR)/sync.c $(SRC_DIR)/mutex_utils.c $(SRC_DIR)/exit_utils.c 

OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM              = rm -f
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -I$(INC_DIR) -pthread -g

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
