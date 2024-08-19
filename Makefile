# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostian <akostian@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 13:20:29 by akostian          #+#    #+#              #
#    Updated: 2024/08/19 18:18:18 by akostian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SERVER_NAME		= server
CLIENT_NAME		= client

NAMES			= $(SERVER_NAME) $(CLIENT_NAME)

SRC_DIR			= src
SERVER_SRCS		= server.c
CLIENT_SRCS		= client.c

INCLUDES		= -Iinclude

BUILD_DIR		= build
LIBFT_DIR		= libft
SERVER_OBJS		= $(addprefix $(BUILD_DIR)/, $(SERVER_SRCS:%.c=%.o))
CLIENT_OBJS		= $(addprefix $(BUILD_DIR)/, $(CLIENT_SRCS:%.c=%.o))

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

RM				= rm -rf



all: $(NAMES)
#


$(SERVER_NAME): $(SERVER_OBJS) $(CLIENT_OBJS)
	make -C $(LIBFT_DIR)

	$(CC) $(CFLAGS) $(INCLUDES) -o $(SERVER_NAME) $(SERVER_OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(LIBFT_DIR)/libft.a
#


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
#


$(SERVER_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
#


$(CLIENT_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
#


clean:
	make clean -C $(LIBFT_DIR)

	$(RM) $(BUILD_DIR)
#


fclean:
	make fclean -C $(LIBFT_DIR)

	$(RM) $(BUILD_DIR) $(NAMES)
#


re: fclean all
#



.PHONY: all clean fclean re