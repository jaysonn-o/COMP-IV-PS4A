CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic -g -Werror
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
DEPS = Sokoban.hpp
SRCS = main.cpp Sokoban.cpp
OBJS = $(SRCS:.cpp=.o)

all: Sokoban Sokoban.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

Sokoban: $(OBJS)
	$(CC) $(CFLAGS) -o Sokoban $(OBJS) $(LIBS)

Sokoban.a: $(OBJS)
	ar rcs Sokoban.a $(OBJS)

clean:
	rm -f Sokoban Sokoban.a *.o

lint:
	cpplint *.cpp *.hpp
