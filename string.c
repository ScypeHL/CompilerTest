#include "header.h"

void string_init(chaa* dest, char* src)
{
    dest->length = strlen(src);
    memcpy(dest->text, src, dest->length + 1);
}

size_t string_length(chaa* str){ return str->length;}
