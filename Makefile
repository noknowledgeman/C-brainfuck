CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -g

TARGET_DIR=./target
SOURCE_DIR=./src

TARGET=$(TARGET_DIR)/brainfuck

$(TARGET): ./target/main.o ./target/lexer.o ./target/interpreter.o 
	$(CC) $(CFLAGS) -o $@ $^ -lm

./target/lexer.o: ./src/lexer.c ./src/lexer.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

./target/interpreter.o: ./src/interpreter.c ./src/interpreter.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

./target/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c -o $@ $^ -lm

.PHONY: run clean
run: $(TARGET)
	./$<

clean:
	rm -f ./target/*
	