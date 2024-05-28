# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaiz <mbaiz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 10:49:59 by mbaiz             #+#    #+#              #
#    Updated: 2024/05/15 14:45:41 by mbaiz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a
CSOURCES = client.c
COBJ = $(CSOURCES:%.c=%.o)
SSOURCES = server.c
SOBJ = $(SSOURCES:%.c=%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDES = minitalk.h

all: libs $(SERVER) $(CLIENT)

%.o: %.c $(INCLUDES)
	$(CC) $(FLAGS) -c $<

libs:
	make -C libft
	make -C printf

$(SERVER): $(SOBJ)
	$(CC) $(FLAGS) $^ $(LIBFT) $(PRINTF) -o $@

$(CLIENT): $(COBJ)
	$(CC) $(FLAGS) $^ $(LIBFT) $(PRINTF) -o $@

clean:
	make -C libft fclean
	make -C printf fclean
	rm -f $(COBJ) $(SOBJ)

fclean: clean
	make -C libft fclean
	make -C printf fclean
	rm -rf $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re