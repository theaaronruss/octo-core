# OctoCore

A CHIP-8 emulator written in C

## Dependencies
* SDL3

## Building

### Mac
* Ensure SDL3 is installed
* Build with `gcc -c src/main.c $CFLAGS`
* Link with `gcc main.o $LDFLAGS -lSDL3`
* Run with `./main`

## Keyboard

```
1 2 3 C    1 2 3 4
4 5 6 D => Q W E R
7 8 9 E    A S D F
A 0 B F    Z X C V
```

