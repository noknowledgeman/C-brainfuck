#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/// @brief Generates the jump table necessary for handling the loops
/// @param tokens the token list 
/// @param len then length of the token list
/// @return an array of ints of length len, initialized to -1 with the jumps in.
int *generate_jump_table(Token *tokens, int len) {
    int *jump_table = malloc(sizeof(int)*len);
    memset(jump_table, -1, len*sizeof(int));

    // allowed in c99
    int loop_stack[len];
    int stack_ptr = 0;
    for (int i = 0; i < len; i++) {
        if (tokens[i] == LLoop) {
            loop_stack[stack_ptr++] = i;
        } else if (tokens[i] == RLoop) {
            int last = loop_stack[--stack_ptr];
            jump_table[i] = last;
            jump_table[last] = i;
        }
    }

    return jump_table;
}

/// @brief Tokenizes a string
/// @param \0 terminated string
/// @return array of Tokens of the same length as the string + EOF
struct Tokens *tokenize(const char *str) {
    struct Tokens *token_struct = (struct Tokens *)malloc(sizeof(struct Tokens));

    int str_len = strlen(str);
    Token *tokens = (Token *)calloc(str_len+1, sizeof(Token));

    for (int i = 0; i < str_len; i++) {
        char c = str[i];
        switch (c)
        {
        case '<':
            tokens[i] = Left;
            break;
        case '>':
            tokens[i] = Right;
            break;
        case '+':
            tokens[i] = Plus;
            break;
        case '-':
            tokens[i] = Minus;
            break;
        case '[':
            tokens[i] = LLoop;
            break;
        case ']':
            tokens[i] = RLoop;
            break;
        case '.':
            tokens[i] = Out;
            break;
        case ',':
            tokens[i] = In;
            break;
        // case '#':
        //     tokens[i] = Debug;
        //     break;
        // case '!':
        //     fprintf(stdin, "%s", &str[i]);
        //     i = str_len;
        //     break;
        default:
            continue;
        }
    }
    tokens[str_len] = EOF;

    token_struct->tokens = tokens;
    token_struct->len = str_len+1;
    token_struct->jump_table = generate_jump_table(tokens, str_len+1);
    return token_struct;
}

/// @brief frees the Tokens struct
/// @param tokens 
void free_tokens(struct Tokens *tokens) {
    free(tokens->tokens);
    free(tokens->jump_table);
    free(tokens);
}

void _debug_print(struct Tokens *toke_struct, int len) {
    printf("Tokens: \n");
    for (int i = 0; i < len; i++) {
        printf("%d ", toke_struct->tokens[i]);
    }
    printf("\n");
    printf("Length: %d", toke_struct->len);
    printf("Jump Table: \n");
    for (int i = 0; i < len; i++) {
        printf("%d ", toke_struct->jump_table[i]);
    }
    printf("\n");
}

char *read_file(char *file_path) {
    FILE *file_ptr = fopen(file_path, "r");

    size_t size = 2;
    size_t idx = 0;
    char *file_string = malloc(size);

    char c;
    while ((c = getc(file_ptr)) != EOF) {
        file_string[idx]=c;
        idx++;
        if (idx == size) {
            size *= 2;
            file_string = realloc(file_string, size);
        }
    }
    file_string[idx] = '\0';
    fclose(file_ptr);
    return file_string;
}
