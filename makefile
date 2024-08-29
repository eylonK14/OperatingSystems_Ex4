CC = g++
CFLAGS = -pg -g -Wall -Werror -Wextra
OBJS = hierholzers.o EulerianCycleFinder.o

all: hierholzers hello race

race: Ex7/race.o
	$(CC) $(CFLAGS) -o $@ $^

hello: Ex5-6/hello.o
	$(CC) $(CFLAGS) -o $@ $^

hierholzers: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

*.o: *.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean all

clean:
	rm -f hierholzers Ex5-6/hello Ex7/race *.o Ex5-6/*.o Ex7/*.o gmon.out *.gcov *.gcda *.gcno 

