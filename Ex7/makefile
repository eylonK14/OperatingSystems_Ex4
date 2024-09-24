CC = g++
CFLAGS = -pg -g -Wall -Werror -Wextra -lc -fprofile-arcs -ftest-coverage

all: race

hello: race.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f  race *.o gmon.out *.gcov *.gcda *.gcno