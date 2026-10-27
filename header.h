#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char* text;
    size_t length;
}chaa;

void string_init(chaa* dest, char* src);
