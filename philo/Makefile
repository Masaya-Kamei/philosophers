# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 12:02:43 by mkamei            #+#    #+#              #
#    Updated: 2022/03/01 08:54:30 by mkamei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath   %.c srcs:srcs/utils
SRCSNAME:=	main.c thread.c philo.c philo_end.c str.c time.c mutex.c put.c
SRCSDIR	:=	./srcs
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCNAME))

OBJSDIR	:=	./objs
OBJS	:=	$(addprefix $(OBJSDIR)/, $(SRCSNAME:.c=.o))
DEPS    :=  $(addprefix $(OBJSDIR)/, $(SRCSNAME:.c=.d))

INCLUDE :=	-I./includes/
NAME	:=	philo

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
CFLAGS  +=  -MMD -MP
RM      :=  rm -rf

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJS)

$(OBJSDIR)/%.o	:	%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

-include $(DEPS)

clean		:
				$(RM) $(OBJS)

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
