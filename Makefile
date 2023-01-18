FT_NAME =	ft_test
STD_NAME =	std_test
FT_SRCS =	./tester/ft_test.cpp
STD_SRCS =	./tester/std_test.cpp
CC =		c++
FLAGS =		-Wall -Wextra -Werror -std=c++98
FT_OBJS =	${FT_SRCS:.cpp=.o}
STD_OBJS =	${STD_SRCS:.cpp=.o}

.PHONY: all
.PHONY: ft_name
.PHONY: std_name
.PHONY: clean
.PHONY: fclean
.PHONY: re
.PHONY: push

all: std_name ft_name

push:
		./ft_test > ft_test.txt
		./std_test > std_test.txt

ft_name: $(FT_NAME)

std_name: $(STD_NAME)

diff:
	diff ft_test.txt std_test.txt

clean:
	rm -f $(FT_OBJS) $(STD_OBJS)

fclean: clean
	rm -f $(FT_NAME) $(STD_NAME)
	rm -rf std_test.txt ft_test.txt
	rm -rf std_time.txt ft_time.txt

re: fclean all

$(STD_NAME): $(STD_OBJS)
	$(CC) $(STD_OBJS) -o $(STD_NAME)

$(STD_OBJS): %.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(FT_NAME): $(FT_OBJS)
	$(CC) $(FT_OBJS) -o $(FT_NAME)

$(FT_OBJS): %.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@