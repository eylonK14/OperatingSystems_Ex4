CC = g++
CFLAGS = -pg -g -Wall -Werror -Wextra -lc -fprofile-arcs -ftest-coverage
OBJS = hierholzers.o EulerianCycleFinder.o

all: hierholzers

hierholzers: $(OBJS)
	g++ -pg -g -Wall -Werror -Wextra -lc -fprofile-arcs -ftest-coverage -o $@ $^

hierholzers.o:
	$(CC) $(CFLAGS) hierholzers.cpp -o hierholzers.o -c

EulerianCycleFinder.o:
	$(CC) $(CFLAGS) EulerianCycleFinder.cpp -o EulerianCycleFinder.o -c

#*.o: *.cpp
#g++ -pg -g -Wall -Werror -Wextra -lc -fprofile-arcs -ftest-coverage -o $^

.PHONY: clean all

clean:
	rm -f hierholzers *.o gmon.out *.gcov *.gcda *.gcno