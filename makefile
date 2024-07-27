CC = g++
CFLAGS = -pg -g -Wall -Werror -Wextra
OBJS = hierholzers.o EulerianCycleFinder.o

all: hierholzers

hierholzers: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

*.o: *.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f hierholzers *.o gmon.out *.gcov *.gcda *.gcno

.PHONY: clean all
