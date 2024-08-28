CC = g++
CFLAGS = -pg -g -Wall -Werror -Wextra
OBJS = hierholzers.o EulerianCycleFinder.o

all: hierholzers hello

hello: hello.o
	$(CC) $(CFLAGS) -o $@ $^

hierholzers: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

*.o: *.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean all

clean:
	rm -f hierholzers hello *.o gmon.out *.gcov *.gcda *.gcno

