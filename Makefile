CC := gcc

octocore: main.o
	$(CC) $^ $(LDFLAGS) -lSDL3 -o octocore

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

.PHONY: clean
clean:
	rm -f octocore
	rm -f *.o

