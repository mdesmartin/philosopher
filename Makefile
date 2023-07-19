NAME = philosopher
DEBUG = no

CFLAGS = -Wall -Wextra -Werror -pthread
# DFLAGS = -g3 -fsanitize=leak -fsanitize=address -fsanitize=pointer-subtract -fsanitize=pointer-compare -fsanitize=undefined
DGLAGS = -g3 -fsanitize=thread

ifeq ($(DEBUG), yes)
CFLAGS += $(DFLAGS)
endif

DIR_SRC =	sources/

LST_SRC =	main.c				\
			check_arg.c			\
			eat.c				\
			utils.c				\
			utils_lib.c			\
			philo_launcher.c	\
			init_structures.c	\
			init_philosophers.c \
			time.c
			
SOURCES	=	$(addprefix $(DIR_SRC), $(LST_SRC))

DIR_OBJ	=	objects/
OBJECTS = 	$(patsubst $(SOURCES)%.c, $(DIR_OBJ)%.o, $(SOURCES))

HEADERS =	$(DIR_SRC)philosopher.h

#  ==============================  RULES  ==============================  #

all: 
	$(MAKE) $(NAME)

debug :
	@$(MAKE) re DEBUG=yes

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED)$(NAME) fclean done!\n$(END)"

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re debug

#  ===========================  COMPILATION  ===========================  #

$(NAME): $(DIR_OBJ) $(OBJECTS)
	cc $(OBJECTS) $(CFLAGS) -o $(NAME)

$(DIR_OBJ)	:
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(HEADERS)
	echo imhere
	cc $(CFLAGS) -c $< -o $@

#  =============================  OPTIONS  =============================  #

ERASE		= 	\033[2K
RERASE		= 	\r\033[2K
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
ORANGE		=	\033[0;33m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
GRAY_LIGHT	=	\033[0;37m
GRAY_DARK	=	\033[1;30m
RED_LIGHT	=	\033[1;31m
GREEN_LIGHT	=	\033[1;32m
YELLOW 		=	\033[1;33m
BLUE_LIGHT	=	\033[1;34m
VIOLET		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m
END			=	\033[0m
