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

detected_OS := $(shell uname)

OBJS_S=		$(SRCS:%.c=%.o)

CC=gcc

INCL=		-I includes/

ifeq ($(detected_OS),Darwin)        # Mac OS X
    CFLAGS=  -I lib42/includes/ -I ./mlx/    \ 
-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lm #-g3 -fsanitize=address -Wall -Wextra -Werror
endif
ifeq ($(detected_OS),Linux)
    CFLAGS=  -I lib42/includes/ -I ./mlx/    \
-L ./mlx/ -lmlx -lXext -lX11 -lm #-g3 -fsanitize=address -Wall -Wextra -Werror
endif

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