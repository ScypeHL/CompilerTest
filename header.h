#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef enum
{
    TOKEN_ID = -1,
    TOKEN_PRINT,
    TOKEN_TYPE_CHAA,
    TOKEN_TYPE_INT,
    TOKEN_OPARAN,
    TOKEN_CPARAN,
    TOKEN_STRING,
    TOKEN_SEMICOLON,
    TOKEN_EQUALS
}TokenType;

typedef struct
{
    char* text;
    size_t length;
}chaa;

int expect_next(TokenType type);
void string_init(chaa* dest, char* src);
