# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcandido <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/31 14:45:49 by lcandido          #+#    #+#              #
#    Updated: 2020/02/20 21:44:51 by lcandido         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_strlen.c ft_memset.c	ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strdup.c ft_calloc.c ft_strlcpy.c ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strtrim.c

OBJECTS = $(subst .c,.o,$(SRCS))

SRCS_B = ft_lstnew.c ft_lstsize.c ft_lstadd_front.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstadd_back.c

OBJECTS_B = $(subst .c,.o,$(SRCS_B))

all: $(NAME)

$(NAME): $(SRCS)
	@gcc -Wall -Wextra -Werror -c $(SRCS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

bonus: $(OBJECTS_B)

$(OBJECTS_B):
	@gcc -Wall -Wextra -Werror -c $(SRCS_B) $(SRCS)
	@ar rc $(NAME) $(OBJECTS_B) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJECTS) $(OBJECTS_B)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
