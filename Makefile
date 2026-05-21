CC := gcc
OBJ := build

octocore: $(OBJ)/main.o $(OBJ)/cpu.o
	$(CC) $^ $(LDFLAGS) -lSDL3 -o octocore

$(OBJ)/main.o: src/main.c | $(OBJ)
	$(CC) $(CFLAGS) -c src/main.c -o $(OBJ)/main.o

$(OBJ)/cpu.o: src/cpu.c | $(OBJ)
	$(CC) $(CFLAGS) -I./includes -c src/cpu.c -o $(OBJ)/cpu.o

$(OBJ):
	mkdir -p build

.PHONY: clean
clean:
	rm -f octocore
	rm -rf $(OBJ)

