NAME	=	minishell

SRC_DIR	=	src

SRC		=	main.c \
			lexer/lexer.c lexer/lexer_utils.c lexer/tokens.c lexer/free_lexer.c \
			parsing/parsing.c parsing/tree.c parsing/cmd_node.c parsing/rdlist.c parsing/op_node.c \
			parsing/parenthesis.c \
			exit/exit_line.c \
			expand/expand.c expand/expand_utils.c \
			exec/exec.c exec/execve.c exec/exit.c exec/exec_utils.c exec/echo.c \
			debug.c

OBJ_DIR	=	obj

OBJ		=	$(SRC:%.c=%.o)

OBJS	=	$(addprefix $(OBJ_DIR)/, $(OBJ))

########	CC  & FLAGS		########

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./include -g3 -fsanitize=address

########		LIBFT		########

LFT_DIR	=	libft

LIBFT	=	$(LFT_DIR)/libft.a

########		RULES		########

all	:			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT) 
				@$(CC) $(CFLAGS) -L$(LFT_DIR) $^ -o $@ -lreadline


$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
				@echo "making libft..."
				@make -sC $(LFT_DIR)
				@echo "Done !"

clean : 
				@echo "cleaning libft..."
				@make -sC $(LFT_DIR) clean
				@echo "cleaning .o files..."
				@rm $(RM_FLAGS) $(OBJS)
				@echo "Project cleaned !"

fclean :		clean
				@echo "cleaning executable and libft.a"
				@make -sC $(LFT_DIR) fclean
				@rm $(RM_FLAGS) $(NAME)
				@echo "Project fully cleaned"

re:				fclean all

.PHONY:			all clean fclean
