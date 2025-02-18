#include "lexer.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error when finding the path\n");
        return 1;
    }

    char *file_str = read_file(argv[1]);
    printf("%s", file_str);

    struct Tokens *tokens = tokenize(file_str);

    struct Interpreter *interpreter = init_interpreter(tokens);

    interpret(interpreter);

    free_interpreter(interpreter);
    free(file_str);
    return 0;
}
