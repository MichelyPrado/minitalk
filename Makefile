NAME = Minitalk

CL = client
SER = server

INCLUDES = ./includes/
FILES = ./sources/
PATH_LIBFT = ./libft/
PATH_OBJS = ./objects/

client_SRC = ./sources/client.c
server_SRC = ./sources/server.c

OBJ_SV = $(patsubst $(FILES)%.c, $(PATH_OBJS)%.o, $(server_SRC))
OBJ_CL = $(patsubst $(FILES)%.c, $(PATH_OBJS)%.o, $(client_SRC))

LIBFT = $(PATH_LIBFT)libft.a


CFLAGS = -Wall -Werror -Wextra 

all: $(NAME)

$(NAME):  $(CL) $(SER)

$(CL): $(OBJ_CL) $(LIBFT)
	@cc $(CFLAGS) -I $(INCLUDES) -o $(CL) $(OBJ_CL) $(LIBFT)

$(OBJ_CL): $(client_SRC)
	@mkdir -p $(PATH_OBJS)
	@cc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(SER): $(OBJ_SV) $(LIBFT)
	@cc $(CFLAGS) -I $(INCLUDES) -o $(SER) $(OBJ_SV) $(LIBFT)

$(OBJ_SV): $(server_SRC)
	@mkdir -p $(PATH_OBJS)
	@cc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(PATH_LIBFT)

clean: 
	@make clean -C $(PATH_LIBFT)
	rm -rf $(PATH_OBJS)


fclean: clean
	@make fclean -C $(PATH_LIBFT)
	rm $(SER) $(CL)
	

re: fclean all


norm:
	@printf "\n\nNorminette simples\n\n"
	@norminette
	@printf "\n\nNorminette -R CheckHeader\n\n"
	@norminette -R CheckHeader
	@printf "\n\nNorminette -R CheckDefine\n\n"
	@norminette -R CheckDefine

PHONY: all clean fclean re