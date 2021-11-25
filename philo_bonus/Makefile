# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 17:07:27 by mkamei            #+#    #+#              #
#    Updated: 2021/11/25 09:43:00 by mkamei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSNAME=	main.c philo.c utils/str.c utils/time.c utils/sem.c utils/put.c
SRCSDIR	=	./srcs
SRCS	=	$(addprefix $(SRCDIR)/, $(SRCNAME))

OBJSNAME=	$(SRCSNAME:.c=.o)
OBJSDIR	=	./objs
OBJS	=	$(addprefix $(OBJSDIR)/, $(OBJSNAME))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	philo_bonus
INCLUDE =	-I./includes/

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJS)

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean		:
				-rm -f $(OBJS)

fclean		:
				-rm -f $(NAME) $(OBJS)

re			:	fclean all

address		:	CC		=	gcc
address		:	CFLAGS	+=	-g -fsanitize=address
address		:	re

leak		:	CC		=	/usr/local/opt/llvm/bin/clang
leak		:	CFLAGS	+=	-g -fsanitize=leak
leak		:	re

thread		:	CC		=	gcc
thread		:	CFLAGS	+=	-g -fsanitize=thread
thread		:	re

.PHONY		:	all clean fclean re address leak thread
