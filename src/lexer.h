#ifndef LEXER_H
#define LEXER_H

typedef enum Token {
    Left,
    Right,
    Plus,
    Minus,
    LLoop,
    RLoop,
    Out,
    In,
    Debug,
} Token;

struct Tokens {
    Token *tokens;
    int len;
    int *jump_table;
};

struct Tokens *tokenize(const char *);
void free_tokens(struct Tokens *);
char *read_file(char *);

void _debug_print(struct Tokens *, int );

#endif