NAME = ft_containers

SRCS = main.cpp

INCLUDE = iterators/iterator.hpp \
	iterators/iterator_traits.hpp \
	iterators/reverse_iterator.hpp \
	utility.hpp \
	vector.hpp

OBJCS = $(SRCS:.cpp=.o)

CPP = clang++ -std=c++98

RM = /bin/rm -rf

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

${NAME} : ${OBJCS} $(INCLUDE)
	@ ${CPP} ${CFLAGS} ${SRCS} -o $@

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean :
	@ ${RM} ${OBJCS}

fclean : clean
	@ ${RM} ${NAME}

re: fclean all