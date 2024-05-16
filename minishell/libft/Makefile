# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwurch <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 12:10:54 by mwurch            #+#    #+#              #
#    Updated: 2022/11/30 12:10:56 by mwurch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################
########################libft
###############################################################

NAME := libft.a
#for creating a static library

AR := @ar v

RM := rm -f
#cc compilation
CC := cc

# automatically add the -I onto each include directory
CFLAGS := -Wall -Werror -Wextra -g
# ALL FUNTIONS that are mendetorie for the Programm
CFILES := 	ft_isalpha.c\
			ft_atoi.c\
			ft_bzero.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_strncmp.c\
			ft_strchr.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_itoa.c\
			ft_split.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_strtrim.c

SRCS_BONUS :=	ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c    
	
#Header
HEADER := libft.h
# regular expression replacement
OBJECTS := $(patsubst %.c, %.o, $(CFILES))

OBJECT_BONUS := $(patsubst %.c, %.o, $(SRCS_BONUS))

###############################################################
########################COMPILING
###############################################################

all: $(NAME)

# create the static library libtest
$(NAME): $(OBJECTS)

	@${AR} -rcs $@ $^

# create for every c file a obeject file
%.o: %.c
	@${CC} -c ${CFLAGS} $< -o $@

bonus: $(OBJECT_BONUS)
	@${AR} -rcs $(NAME) $(OBJECT_BONUS)
  
###############################################################
########################re
###############################################################

re: fclean all

###############################################################
########################CLEAN
###############################################################

clean:
		$(RM) $(OBJECTS) $(OBJECT_BONUS)
# shell commands are a set of kesystrokes away
fclean: clean
		${RM} $(NAME)

###############################################################
########################TEST/DEBUGGING
###############################################################

.PHONY: all make clean fclean re install distclean TAGS info check
	

