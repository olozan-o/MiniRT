# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: olozano- <olozano-@student.42.fr>		  +#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2021/11/28 11:49:48 by olozano-		  #+#	#+#			  #
#	Updated: 2021/11/28 18:49:47 by olozano-		 ###   ########.fr		#
#																			  #
# **************************************************************************** #

NAME	=	miniRT

SRCS	= 	srcs/main_calls.c \
			srcs/read_rt.c \
			srcs/errors.c \
			srcs/ft_calloc.c \
			srcs/str_utils.c \
			srcs/ft_split.c \
			srcs/prepare_to_show.c \
			srcs/struct_fts.c \
			srcs/process_elements1.c \
			srcs/process_elements2.c \
			srcs/math_calculs.c \
			srcs/intersections.c \
			srcs/vector_operations.c \
			srcs/light_color.c

OBJS_S=		$(SRCS:%.c=%.o)

CC=gcc

INCL=		-I includes/

CFLAGS=  -I lib42/includes/ -I ./mlx/	\
-L ./mlx/ -lmlx -lXext -lX11 -lm -g3 #-fsanitize=address #-Wall -Wextra -Werror

all: $(NAME)

lib:
	$(MAKE) -C mlx

$(NAME): lib
	$(CC) $(SRCS) -o $(NAME) $(CFLAGS) $(INCL)

clean:
	rm -f $(OBJS_S)
	rm -f $(OBJS_BNS)
	$(MAKE) clean -C mlx

fclean: clean
	rm -f $(NAME)

re: fclean all