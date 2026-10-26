#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *file;
int bytes;
char buf[1024000];
int _index = 0;

typedef enum
{
    TOKEN_OPARAN,
    TOKEN_CPARAN,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_SEMICOLON
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

        if(ch == '\n' || ch == '\n' || ch == ' ')
      {

      }
      else
      {
          if(ch == '#'){for(;buf[_index] !='\n'; _index++){}}
          if(ch == '"')
          {
              _index++;
              for(tokenBufCursor = 0; '"' != buf[_index]; _index++)
              {
                  //printf("%s\n", tokenBuf);
                  tokenBuf[tokenBufCursor] = buf[_index];
                  tokenBufCursor++;
              }
              strcpy(tokens[tokenCursor].value, tokenBuf);
              tokens[tokenCursor].type = TOKEN_STRING;
              tokenBufCursor = 0;
              tokenCursor++;
              return;
          }
          else if(isalpha(ch))
          {
              for(tokenBufCursor = 0; 0 != isalnum(buf[_index]); _index++)
              {
                  tokenBuf[tokenBufCursor] = buf[_index];
                  tokenBufCursor++;
              }
              //tokenBuf[tokenBufCursor + 1] = '\0';
              strcpy(tokens[tokenCursor].value, tokenBuf);
              tokens[tokenCursor].type = TOKEN_KEYWORD;
              tokenBufCursor = 0;
              tokenCursor++;
              return;
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
          }
      }
}

int main(int argc, char const *argv[])
{
    //if (argc < 2){printf("Deposit a file to compile!\n"); return 1;}
    //argv[1]

    file = fopen("test.rpt", "r");
    if (!file) {printf("File could not found\n"); return 1;}

    fseek(file, 0 , SEEK_END);
    bytes = ftell(file);
    fseek(file, 0 , SEEK_SET);

    printf("%d\n", fread(buf, sizeof(char), bytes, file));
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

    return 0;
}
