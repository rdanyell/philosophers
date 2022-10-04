# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 12:33:05 by rdanyell          #+#    #+#              #
#    Updated: 2022/05/26 13:04:57 by rdanyell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_PH		= philo

HEADER_PH	= philosophers.h

FILES_PH	= main.c utils.c init.c eat.c monitor.c

SRCS_PH		= $(FILES_PH)

OBJS_PH		= $(SRCS_PH:%.c=%.o)

CC 			=  gcc -pthread

CFLAGS		= -Wall -Wextra -Werror 
.PHONY: 	all clean fclean re bonus

all:		$(NAME_PH)

$(NAME_PH):	$(OBJS_PH)
			$(CC) $(CFLAGS) $(OBJS_PH) -o $@

%.o:		%.c $(HEADER_PH) Makefile
			$(CC) $(CFLAGS) -c -o $@ $<

clean	:
			$(RM) $(OBJS_PH)
							
fclean	:	clean
			rm -r $(NAME_PH)

re		:	fclean all
	
