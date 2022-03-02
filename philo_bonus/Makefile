# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 17:07:27 by mkamei            #+#    #+#              #
#    Updated: 2022/03/02 12:11:46 by mkamei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath   %.c srcs:srcs/process:srcs/utils

SRCSNAME:=	main.c process.c entire_monitor.c \
			routine.c monitor.c put_status.c \
			str.c time.c sem.c exit.c create_str.c
SRCSDIR	:=	./srcs
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCNAME))

OBJSDIR	:=	./objs
OBJS	:=	$(addprefix $(OBJSDIR)/, $(SRCSNAME:.c=.o))
DEPS	:=	$(addprefix $(OBJSDIR)/, $(SRCSNAME:.c=.d))

NAME	:=	philo_bonus
INCLUDE :=	-I./includes/

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS	:=	-MMD -MP
RM		:=	rm -rf

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) -pthread $(INCLUDE) -o $@ $(OBJS)

$(OBJSDIR)/%.o	:	%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

-include $(DEPS)

clean		:
				$(RM) $(OBJS) $(DEPS)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

address		:	CFLAGS	+=	-g -fsanitize=address
address		:	re

leak		:	CC		=	/usr/local/opt/llvm/bin/clang
leak		:	CFLAGS	+=	-g -fsanitize=leak
leak		:	re

thread		:	CFLAGS	+=	-g -fsanitize=thread
thread		:	re

.PHONY		:	all clean fclean re address leak thread
