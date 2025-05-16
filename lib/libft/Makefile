# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 11:13:31 by aranger           #+#    #+#              #
#    Updated: 2024/04/02 16:58:47 by nledent          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_isdigit.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_atoi.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strlen.c \
			ft_strrchr.c \
			ft_strchr.c \
			ft_strncmp.c \
			ft_strcmp.c \
			ft_strtrim.c \
			ft_strjoin.c \
			ft_strnstr.c \
			ft_split.c \
			ft_free_split.c \
			ft_itoa.c \
			ft_count_word.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_fstrjoin.c \
			ft_printf/ft_print_adress.c \
			ft_printf/ft_print_others.c \
			ft_printf/ft_print_unsigned.c \
			ft_printf/ft_printf.c \
			get_next_line/get_next_line_utils.c \
			get_next_line/get_next_line.c \
			ft_printf_fd/ft_print_fd_adress.c \
			ft_printf_fd/ft_print_fd_others.c \
			ft_printf_fd/ft_print_fd_unsigned.c \
			ft_printf_fd/ft_printf_fd.c \

SRC			= $(addprefix src/, $(SRCS))

OBJS		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_OBJS		= mkdir -p $(@D)

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g
NAME 		= libft.a

RM 			= rm -f
RM_OBJ		= rm -rf
AR 			= ar -rcs

#-RULES-#

all: 			${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@$(D_OBJS)
				$(CC) $(CFLAGS) -c -o $@ $<

${NAME}: 		${OBJS}
				${AR} ${NAME} ${OBJS}

clean:
				${RM_OBJ} ${OBJ_DIR}

fclean: 		clean
				${RM} ${NAME}

re:				fclean all

.PHONY : 		all clean fclean re 
