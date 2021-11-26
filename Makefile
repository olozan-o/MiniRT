SRCS	= srcs/main_calls.c srcs/read_rt.c srcs/str_utils.c srcs/ft_calloc.c srcs/ft_split.c srcs/prepare_to_show.c srcs/struct_fts.c srcs/errors.c srcs/process_elements1.c srcs/math_calculs.c

OBJS	= ${SRCS:.c=.o}


NAME	= bsq

RM		= rm -f

CC		= gcc

INCLS	= includes

LIBMLX 	= libmlx.dylib \
		libmlx.a

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCLS}
			@echo "Compiled "$<" successfully!"

${NAME}:	${OBJS}
			@make -C ./minilibx_mms
			@make -C ./minilibx_opengl
			@cp ./minilibx_mms/libmlx.dylib libmlx.dylib
			@cp ./minilibx_opengl/libmlx.a libmlx.a
			${CC} -I${INCLS} ${CFLAGS} $(LIBMLX) -o ${NAME} ${OBJS} 
		
clean:
			${RM} ${OBJS}

all:		${NAME}
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

fmlxclean:	fclean
			${RM} libmlx.a
			${RM} libmlx.dylib

re:			fclean all

bonus:		${OBJS_B}
			${CC} -I${INCLS} ${CFLAGS} -o ${NAME} ${OBJS_B}

.PHONY:		all clean fclean re
