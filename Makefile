# **************************************************************************** #
#                                                                              #
#                                                            :::      :::::::  #
#    Makefile                                              :+:      :+:    :+: #
#                                                        +:+ +:+         +:+   #
#    By: yagunduz <yagunduz@student.42istanbul.com.tr> +#+  +:+       +#+      #
#                                                    +#+#+#+#+#+   +#+         #
#    Created: 2025/12/27 10:27:11 by yagunduz             #+#    #+#           #	
#    Updated: 2026/01/20 22:15:23 by yagunduz            ###   ########.tr     #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = minitalk.h

SRCS_S = server.c utils.c
SRCS_C = client.c utils.c
SRCS_S_B = bonus/server_bonus.c bonus/utils_bonus.c
SRCS_C_B = bonus/client_bonus.c bonus/utils_bonus.c

OBJS_S = $(SRCS_S:.c=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS_S_B = $(SRCS_S_B:.c=.o)
OBJS_C_B = $(SRCS_C_B:.c=.o)

all: $(SERVER) $(CLIENT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(OBJS_S)
	$(CC) $(CFLAGS) $(OBJS_S) -o $(SERVER)

$(CLIENT): $(OBJS_C)
	$(CC) $(CFLAGS) $(OBJS_C) -o $(CLIENT)

bonus: fclean $(OBJS_S_B) $(OBJS_C_B)
	$(CC) $(CFLAGS) $(OBJS_S_B) -o $(SERVER)
	$(CC) $(CFLAGS) $(OBJS_C_B) -o $(CLIENT)

clean:
	rm -rf $(OBJS_S) $(OBJS_C) $(OBJS_S_B) $(OBJS_C_B)

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all bonus clean fclean re
