.PHONY: all, $(NAME), clean, fclean, re

NAME = ft_ls

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

cc = gcc
C_FLAGS = -Wall -Wextra -Werror
FRAM = 

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./include/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = ft_ls.h
SRC_NAME = parser.c list.c print_tools.c sort.c utils.c print.c main.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@echo
		@make -C $(LFT_PATH)
		@$(CC) -o $(NAME) -L $(LFT_PATH) -lft $^ -o $@
		@echo "\033[32mFT_LS ready.\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<
		@echo -n =

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "\033[32mDeleting [./obj] directory.\033[0m"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "\x1b[31mSUCESSFULLY CLEANED FT_LS\x1b[31m"

re: fclean all