# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yagunduz <yagunduz@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/27 10:27:11 by yagunduz          #+#    #+#              #
#    Updated: 2025/12/30 19:57:28 by yagunduz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS_SERVER	= server.c utils.c
SRCS_CLIENT	= client.c utils.c

SRCS_SERVER_BONUS = bonus/server_bonus.c bonus/utils_bonus.c
SRCS_CLIENT_BONUS = bonus/client_bonus.c bonus/utils_bonus.c

ifdef BONUS
OBJS_SERVER	= $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT	= $(SRCS_CLIENT_BONUS:.c=.o)
else
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
endif

OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

NAME_SERVER	= server
NAME_CLIENT	= client

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

bonus: 
	@$(MAKE) BONUS=1 all

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	rm -f $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

norm:
	@norminette $(SRCS_SERVER) $(SRCS_CLIENT) minitalk.h
	@norminette $(SRCS_SERVER_BONUS) $(SRCS_CLIENT_BONUS) bonus/minitalk_bonus.h

.PHONY: all clean fclean re bonus norm