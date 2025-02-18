#include "interpreter.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

struct Interpreter *init_interpreter(struct Tokens* tokens) {
    struct Interpreter* interpreter = calloc(1, sizeof(struct Interpreter));

    interpreter->arr = calloc(NUM_CELLS, sizeof(unsigned char));
    interpreter->program = tokens;
    return interpreter;
}

void free_interpreter(struct Interpreter *interpreter) {
    free(interpreter->arr);
    free_tokens(interpreter->program);
    free(interpreter);
}

void interpret(struct Interpreter *intr) {
    for (int i = 0; i < intr->program->len; i++) {
        Token tok = intr->program->tokens[i];
        switch (tok)
        {
        case Left:
            if (intr->pointer == 0) {
                intr->pointer = NUM_CELLS-1;
            } else {
                intr->pointer--;
            }
            break;
        case Right:
            intr->pointer = (intr->pointer+1)%NUM_CELLS;
            break;
        case Plus:
            intr->arr[intr->pointer]++;
            break;
        case Minus:
            intr->arr[intr->pointer]--;
            break;
        case LLoop:
            if (!intr->arr[intr->pointer]) {
                i = intr->program->jump_table[i];
            }
            break;
        case RLoop:
            if (intr->arr[intr->pointer]) {
                i = intr->program->jump_table[i];
            }
            break;
        case Out:
            putchar(intr->arr[intr->pointer]);
            break;
        case In:
            intr->arr[intr->pointer] = getchar();
            break;
        case Debug: 
        default:
            break;
        }
    }
}

