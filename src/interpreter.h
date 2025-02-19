#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "lexer.h"


#define NUM_CELLS 30000
#define DEBUG_CELLS 20

struct Interpreter {
    struct Tokens *program;
    unsigned char *arr;
    int pointer;
};

struct Interpreter *init_interpreter(struct Tokens *);
void free_interpreter(struct Interpreter *);
void interpret(struct Interpreter *);
#endif