#Exit
NAME		= 	philo

#Sources
SRCS		= 	philosophers.c \
				check_input.c \
				utils.c \
				create_threads.c \
				routines.c \
				time_functions.c \
				check_death.c

OBJS		= 	$(SRCS:.c=.o)

#Compilation
# Linking: option -r to ensure that if the library (.a) file already exists, 
# it will be replaced. The command option -c should be used so that if the 
# file doesn’t exist, it will be created.
AR			=	ar -rcs
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -pthread #-g3 -fsanitize=thread #-fsanitize=undefined #undefined address thread #-O3 -march=native 

#Erase
RM			= 	rm -rf

#Default target
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

#Cleaning objects and executable 
fclean:		clean
			$(RM) $(NAME)

#Cleaning all and then compilation
re:			fclean all

#Exectute no matter name is
.PHONY: all clean fclean re
