#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define KEYWORD_COUNT 3

typedef enum
{
    TOKEN_ID = -1,
    TOKEN_PRINT,
    TOKEN_TYPE_CHAA,
    TOKEN_TYPE_INT,
    TOKEN_CHAA,
    TOKEN_INT,
    TOKEN_OPARAN,
    TOKEN_CPARAN,
    TOKEN_STRING,
    TOKEN_SEMICOLON,
    TOKEN_EQUALS,
    TOKEN_PLUS
}TokenType;

typedef enum
{
    ID_CHAR,
    ID_INT
}IdentifierType;

typedef struct
{
    FILE *file;
    size_t size;
    char buf[1024000];
    int index;
}FD;

typedef struct
{
    TokenType type;
    IdentifierType itype;

    char value[1024];
    void* data;
}Token;

typedef struct
{
    char* text;
    size_t length;
}chaa;

int process(FD *inFile, FD *outFile);

void tokenize(FD *file);
void print_tokens();

void start_print();

int numberizer(char* numberAsString);
int expect_cornered(TokenType type);
int expect_next(TokenType type);
void string_init(chaa* dest, char* src);
