NAME = ft_containers

SRCS_VECTOR = mains/main_vector.cpp
SRCS_STACK = mains/main_stack.cpp
SRCS_MAP =	mains/main_map.cpp

INCLUDE = utils/iterator.hpp \
	utils/iterator_traits.hpp \
	utils/reverse_iterator.hpp \
	map/map.hpp \
	utils/AVL.hpp \
	stack/stack.hpp \
	utils/utility.hpp \
	vector/vector.hpp  \
	map/map_iterator.hpp \

OBJCS_VECTOR = $(SRCS_VECTOR:.cpp=.o)
OBJCS_STACK = $(SRCS_STACK:.cpp=.o)
OBJCS_MAP = $(SRCS_MAP:.cpp=.o)

CPP = c++ -std=c++98

CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -rf

vector: $(OBJCS_VECTOR) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS_VECTOR} -o $(NAME)

stack: $(OBJCS_STACK) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS_STACK} -o $(NAME)

map: $(OBJCS_MAP) $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS_MAP} -o $(NAME)

clean :
	@ ${RM} ${OBJCS_VECTOR} $(OBJCS_STACK) $(OBJCS_MAP)

fclean : clean
	@ ${RM} ${NAME}

re: fclean vector stack map