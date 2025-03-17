CC=gcc
CFLAGS=-std=c2x -pedantic -Wall -g

TARGET_DIR=./target
SOURCE_DIR=./src

TARGET=$(TARGET_DIR)/brainfuck

$(TARGET): ./target/main.o ./target/lexer.o ./target/interpreter.o ./target/compiler.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(TARGET_DIR)/compiler.o: $(SOURCE_DIR)/compiler.c $(SOURCE_DIR)/compiler.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

$(TARGET_DIR)/lexer.o: $(SOURCE_DIR)/lexer.c $(SOURCE_DIR)/lexer.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

$(TARGET_DIR)/interpreter.o: $(SOURCE_DIR)/interpreter.c $(SOURCE_DIR)/interpreter.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

$(TARGET_DIR)/main.o: $(SOURCE_DIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $^ -lm

.PHONY: run clean
run: $(TARGET)
	./$<

clean:
	rm -f ./target/*
	