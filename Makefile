# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 10:54:15 by chaueur           #+#    #+#              #
#    Updated: 2018/05/11 15:56:03 by chaueur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ParticleSystem
TEST			= test
CC				= clang++ -std=c++11

FLAG			= -O2 -Wall -Werror -Wextra -pedantic -Wno-missing-field-initializers
FRAMEWORK		= 	-framework Cocoa -framework IOKit \
					-framework CoreVideo -framework OpenCL -framework OpenGL \
					-framework SDL2
INCS			= 	-I include -I /Library/Frameworks/SDL2.framework/Headers \
					-I ft_printf/inc/ -I glm

DIR_SRC			= src/

DIR_INC			= include/
DIR_OBJ			= obj/

SRC_MAIN		= main.cpp particlemanager.cpp clmanager.cpp utils.cpp window.cpp

SRCS			= $(SRC_MAIN)

OBJS			= $(SRCS:.cpp=.o)

SRC				= $(SRC_MAIN)

OBJ				= $(addprefix $(DIR_OBJ),$(OBJS))

DEP				= $(OBJ:.o=.d)

VPATH			= $(DIR_SRC)

LIBFTPRINTF		= ft_printf/libftprintf.a

all: $(NAME)

debug: FLAG += -g -Wno-unused-parameter -Wno-unused-function \
-Wno-unused-variable -Wno-uninitialized -Wno-unused-private-field
debug: $(NAME)

$(NAME): $(LIBFTPRINTF) $(OBJ)
	$(CC) $(FRAMEWORK) $^ -o $@

$(LIBFTPRINTF):
	@make -C ft_printf/

$(DIR_OBJ)%.o: %.cpp
	@mkdir $(DIR_OBJ) 2> /dev/null || true
	$(CC) $(FLAG) $(INCS) -o $@ -c $< -MMD -MP

clean:
	@make -C ft_printf/ clean
	rm -fv $(OBJ)
	@rmdir $(DIR_OBJ) 2> /dev/null || true

fclean: clean
	@make -C ft_printf/ fclean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONE: all, clean, fclean, re
