# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbadaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 14:43:30 by mbadaoui          #+#    #+#              #
#    Updated: 2023/02/19 14:43:30 by mbadaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
NAME_VECTOR = ft_containers_vector
NAME_STACK = ft_containers_stack
NAME_MAP = ft_containers_map

SRCS = Mains/main.cpp
SRCS_VECTOR = Mains/main_vector.cpp
SRCS_STACK = Mains/main_stack.cpp
SRCS_MAP =	Mains/main_map.cpp

INCLUDE = Utils/iterator.hpp \
	Utils/iterator_traits.hpp \
	Utils/reverse_iterator.hpp \
	Map/map.hpp \
	Utils/AVL.hpp \
	Stack/stack.hpp \
	Utils/utility.hpp \
	Vector/vector.hpp  \
	Map/map_iterator.hpp \

OBJCS = $(SRCS:.cpp=.o)
OBJCS_VECTOR = $(SRCS_VECTOR:.cpp=.o)
OBJCS_STACK = $(SRCS_STACK:.cpp=.o)
OBJCS_MAP = $(SRCS_MAP:.cpp=.o)

CPP = c++ -std=c++98

CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -rf

all: $(NAME)

$(NAME): $(OBJCS) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS} -o $(NAME)

vector: $(NAME_VECTOR)

$(NAME_VECTOR): $(OBJCS_VECTOR) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS_VECTOR} -o $(NAME_VECTOR)

stack: $(NAME_STACK)

$(NAME_STACK): $(OBJCS_STACK) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS_STACK} -o $(NAME_STACK)

map: $(NAME_MAP)

$(NAME_MAP): $(OBJCS_MAP) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS_MAP} -o $(NAME_MAP)

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean :
	@ ${RM} $(OBJCS) ${OBJCS_VECTOR} $(OBJCS_STACK) $(OBJCS_MAP)

fclean : clean
	@ ${RM} ${NAME} $(NAME_VECTOR) $(NAME_STACK) $(NAME_MAP)

re: fclean all
