CC = g++
CFLAGS = -pg -g -Wall -Werror -Wextra -lc -fprofile-arcs -ftest-coverage

all: hello

hello: hello.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f  hello *.o gmon.out *.gcov *.gcda *.gcno
