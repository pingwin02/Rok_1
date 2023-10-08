.PHONY: all
all: ls

CC = gcc

ls: ls.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o ls
	rm -f valgrind-out.txt
leaks:
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--log-file=valgrind-out.txt \
			./ls