#include "header.h"

FILE *file;
FILE *outFile;
int bytes;
char buf[1024000];
int _index = 0;

char out[1024000];

#define KEYWORD_COUNT 2
char* keywords[KEYWORD_COUNT];

typedef enum
{
    TOKEN_ID = -1,
    TOKEN_TYPE_CHAA,
    TOKEN_PRINT,
    TOKEN_OPARAN,
    TOKEN_CPARAN,
    TOKEN_STRING,
    TOKEN_SEMICOLON,
    TOKEN_EQUALS
}Token_Type;

typedef struct
{
    Token_Type type;
    char value[1024];
}Token;

Token tokens[1024];
int tokenCursor = 0;

void tokenize(char ch)
{
    char tokenBuf[1024];
    int tokenBufCursor = 0;
    memset(tokenBuf, 0, (strlen(tokenBuf) + 1) * sizeof(char));

        if(ch == '\n' || ch == '\n' || ch == ' ')
      {

      }
      else
      {
          if(ch == '#'){for(;buf[_index] !='\n'; _index++){}}
          if(ch == '"')
          {
              tokenBuf[tokenBufCursor] = 34;
              tokenBufCursor++;
              _index++;
              for(; '"' != buf[_index]; _index++)
              {
                  tokenBuf[tokenBufCursor] = buf[_index];
                  printf("Characters %c\n", buf[_index]);
                  tokenBufCursor++;
              }
              tokenBuf[tokenBufCursor] = 34;
              tokenBufCursor++;
              //strcpy(tokens[tokenCursor].value, tokenBuf);
              printf("Length: %d\n", tokenBufCursor);
              memcpy(tokens[tokenCursor].value, tokenBuf, sizeof(char) * (tokenBufCursor));
              tokens[tokenCursor].type = TOKEN_STRING;
              tokenBufCursor = 0;
              tokenCursor++;
          }
          else if(isalpha(ch))
          {
              for(tokenBufCursor = 0; 0 != isalpha(buf[_index]); _index++)
              {
                  tokenBuf[tokenBufCursor] = buf[_index];
                  tokenBufCursor++;
              }
              //tokenBuf[tokenBufCursor + 1] = '\0';
              int i;
              for(i = 0; i < KEYWORD_COUNT; i++)
              {
                  if(!strcmp(keywords[i], tokenBuf))
                  {
                    tokens[tokenCursor].type = i;
                    break;
                  }else{tokens[tokenCursor].type = TOKEN_ID;}
              }
              printf("Length: %d\n", tokenBufCursor);
              memcpy(tokens[tokenCursor].value, tokenBuf, sizeof(char) * (tokenBufCursor));
              //strcpy(tokens[tokenCursor].value, tokenBuf);
              tokenBufCursor = 0;
              tokenCursor++;
          }
          switch(buf[_index])
          {
              case '(':
                  strcpy(tokens[tokenCursor].value, "(");
                  tokens[tokenCursor].type = TOKEN_OPARAN;
                  tokenCursor++;
                  break;
              case ')':
                  strcpy(tokens[tokenCursor].value, ")");
                  tokens[tokenCursor].type = TOKEN_CPARAN;
                  tokenCursor++;
                  break;
              case ';':
                  strcpy(tokens[tokenCursor].value, ";");
                  tokens[tokenCursor].type = TOKEN_SEMICOLON;
                  tokenCursor++;
                  break;
              case '=':
                  strcpy(tokens[tokenCursor].value, "=");
                  tokens[tokenCursor].type = TOKEN_EQUALS;
                  tokenCursor++;
                  break;
          }
      }
}

void str_builder(char* src, char* dst)
{
    int _i;
    size_t size;
    size = strlen(src);
    char temp[size + 1];
    temp[0] = 34;
    for(_i = 1; temp[_i] != 0; _i++)
    {
        temp[_i] = src[_i - 1];
    }
    temp[_i] = 34;
    temp[_i + 1] = '\0';
    strcat(dst, temp);
}

void process()
{
    outFile = fopen("out.c", "w");
    strcat(out,"#include <stdio.h>\nint main(){");

    for(int i = 0; i < tokenCursor; i++)
    {
        switch(tokens[i].type)
        {
            case TOKEN_ID:
                strcat(out, tokens[i].value);
                break;
            case 0:
                strcat(out, "char* ");
                break;
            case TOKEN_PRINT:
                #ifdef _WIN64
                    strcat(out, "puts");
                #elif __linux__
                    strcat(out, "echo");
                #endif
                break;
            case TOKEN_OPARAN:
                strcat(out, "(");
                break;
            case TOKEN_CPARAN:
                strcat(out, ")");
                break;
            case TOKEN_STRING:
                strcat(out, tokens[i].value);
                //str_builder(tokens[i].value, out);
                break;
            case TOKEN_SEMICOLON:
                strcat(out, ";\n");
                break;
            case TOKEN_EQUALS:
                strcat(out, "=");
                break;
        }
    }
    strcat(out," return 0;}");
    fprintf(outFile, "%s\n", out);
}

int main(int argc, char const *argv[])
{
    //if (argc < 2){printf("Deposit a file to compile!\n"); return 1;}
    //argv[1]
    keywords[1] = "print";
    keywords[0] = "chaa";

    file = fopen("test.rpt", "r");
    if (!file) {printf("File could not found\n"); return 1;}

    fseek(file, 0 , SEEK_END);
    bytes = ftell(file);
    fseek(file, 0 , SEEK_SET);

    printf("Number of characters: %d\n", fread(buf, sizeof(char), bytes, file));
    printf("%s\n", buf);

    for(_index = 0; _index < bytes; _index++)
    {
        tokenize(buf[_index]);
    }
    printf("\n");

    for(int l = 0; l < tokenCursor ; l++)
    {
        printf("Tokens: %s\n", tokens[l].value);
    }
    process();

    chaa testing;
    string_init(&testing, "Hello World!");

    return 0;
}
