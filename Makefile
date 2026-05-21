CC := gcc

octocore: main.o cpu.o
	$(CC) $^ $(LDFLAGS) -lSDL3 -o octocore

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

cpu.o: src/cpu.c
	$(CC) $(CFLAGS) -I./includes -c src/cpu.c

.PHONY: clean
clean:
	rm -f octocore
	rm -f *.o

