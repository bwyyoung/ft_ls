# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/09 10:19:19 by byoung-w          #+#    #+#              #
#    Updated: 2014/12/10 16:19:13 by byoung-w         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME	=	ft_ls
CC		=	gcc
CCO		=	gcc -o
LIB		=	-L libft/ -lft
FLAGS	=	-c -Wall -Werror -Wextra

INC		=	libft/includes/

C_FILES	= ft_ls.c
C_FILES	+= ft_ls_l.c
C_FILES	+= ft_ls_error.c
C_FILES	+= ft_ls_flags.c
C_FILES	+= ft_ls_cmp.c
C_FILES	+= ft_ls_cmp2.c
C_FILES	+= ft_ls_t.c
C_FILES	+= ft_ls_util.c
C_FILES	+= btree_insert_node.c
C_FILES	+= btree_create_node.c
C_FILES	+= btree_print.c
C_FILES	+= btree_search_item.c
C_FILES += ft_ls_r.c
C_FILES += ft_ls_dir.c
C_FILES += ft_ls_params.c

O_FILES	= ft_ls.o
O_FILES	+= ft_ls_l.o
O_FILES	+= ft_ls_error.o
O_FILES	+= ft_ls_flags.o
O_FILES	+= ft_ls_cmp.o
O_FILES	+= ft_ls_cmp2.o
O_FILES	+= ft_ls_t.o
O_FILES	+= ft_ls_util.o
O_FILES	+= btree_insert_node.o
O_FILES	+= btree_create_node.o
O_FILES	+= btree_print.o
O_FILES	+= btree_search_item.o
O_FILES += ft_ls_r.o
O_FILES += ft_ls_dir.o
O_FILES += ft_ls_params.o

all		: $(NAME)

$(NAME)	:
	@make -C libft/ all
	@$(CC) $(FLAGS) -c $(C_FILES) -I $(INC)
	@$(CC) -o $(NAME) $(O_FILES)  $(LIB)

clean	:
	@make -C libft/ clean
	@/bin/rm -f $(O_FILES)

fclean	: clean
	@make -C libft/ fclean
	@/bin/rm -f $(NAME)

re		: fclean all
