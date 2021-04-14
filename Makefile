SRCS	= srcs/main_calls.c srcs/read_rt.c srcs/str_utils.c srcs/ft_calloc.c srcs/ft_split.c srcs/prepare_to_show.c srcs/struct_fts.c srcs/errors.c srcs/process_elements1.c

SRCS_B	= srcs/main_calls.c srcs/read_rt.c srcs/str_utils.c srcs/ft_calloc.c srcs/ft_split.c srcs/prepare_to_show.c srcs/struct_fts.c srcs/errors.c srcs/process_elements1.c

OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS:.c=.o}

NAME	= bsq

RM		= rm -f

CC		= gcc

INCLS	= includes

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCLS}

${NAME}:	${OBJS}
			${CC} -I${INCLS} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS_B}
			${CC} -I${INCLS} ${CFLAGS} -o ${NAME} ${OBJS_B}

.PHONY:		all clean fclean re
