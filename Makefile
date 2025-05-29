#-PATH FILES-#

SRC_DIR			= src
OBJ_DIR			= obj

#-LIBFT-#

LIBFT			= lib/libft
LIBFT_A			= $(LIBFT)/libft.a


SRCS			= \
				main.c \
				parsing.c \
				structure_management.c \
				signal.c \
				send_packets.c \

SRC				= $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_OBJS			= mkdir -p $(@D)

#-UTILS-#

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g 
NAME 			= ft_traceroute
RM 				= rm -f
RMR				= rm -rf

#-RULES-#

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
				@make -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				$(D_OBJS)
				$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): 		$(OBJS) $(LIBFT_A)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) -lm

clean:
				@$(RMR) $(OBJ_DIR)
				@make -C $(LIBFT) clean

fclean: 		clean
				@$(RM) $(NAME)
				@make -C $(LIBFT) fclean

re:				fclean all

.PHONY : 		all clean fclean re bonus