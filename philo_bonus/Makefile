# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdanyell <rdanyell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 12:33:05 by rdanyell          #+#    #+#              #
#    Updated: 2022/05/26 12:08:07 by rdanyell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_PHB	= philo_bonus

HEADER_PHB	= philo_bonus.h

FILES_PHB	= main_bonus.c utils_bonus.c init_bonus.c 

SRCS_PHB	= $(FILES_PHB)

OBJS_PHB	= $(SRCS_PHB:%.c=%.o)

CC 			=  cc -pthread

CFLAGS		= -Wall -Wextra -Werror 

.PHONY: 	all clean fclean re bonus

all:		$(NAME_PHB)

$(NAME_PHB):$(OBJS_PHB)
			$(CC) $(CFLAGS) $(OBJS_PHB) -o $@

%.o:		%.c $(HEADER_PHB) Makefile
			$(CC) $(CFLAGS) -c -o $@ $<

clean	:
			$(RM) $(OBJS_PHB)
							
fclean	:	clean
			rm -r $(NAME_PHB)

re		:	fclean all
	
