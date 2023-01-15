NAME = ft_containers

SRCS = main.cpp

INCLUDE = iterator.hpp \
	iterator_traits.hpp \
	reverse_iterator.hpp \
	utility.hpp \
	vector.hpp

OBJCS = $(SRCS:.cpp=.o)

CPP = c++ -std=c++98

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