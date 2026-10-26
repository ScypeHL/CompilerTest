#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *file;
FILE *outFile;
int bytes;
char buf[1024000];
int _index = 0;

char out[1024000];

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
    memset(tokenBuf, 0, strlen(tokenBuf));

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
                  tokenBuf[tokenBufCursor] = buf[_index];
                  tokenBufCursor++;
              }
              strcpy(tokens[tokenCursor].value, tokenBuf);
              tokens[tokenCursor].type = TOKEN_STRING;
              tokenBufCursor = 0;
              tokenCursor++;
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

void str_builder(char* src, char* dst)
{
    int _i;
    char temp[1024];
    temp[0] = 34;
    for(_i = 1; '\0' != temp[_i]; _i++)
    {
        temp[_i] = src[_i - 1];
    }
    temp[_i] = 34;
    temp[_i + 1] = '\0';
    printf("Result: %s\n", temp);
    strcat(dst, temp);
}

void process()
{
    outFile = fopen("out.c", "w");
    strcat(out,"#include <stdio.h>\nint main(){");

    for(int i = 0; i < tokenCursor; i++)
    {
        printf("Index: %d\n", i);
        switch(tokens[i].type)
        {
            case TOKEN_KEYWORD:
                strcat(out, "printf");
                break;
            case TOKEN_OPARAN:
                strcat(out, "(");
                break;
            case TOKEN_CPARAN:
                strcat(out, ")");
                break;
            case TOKEN_STRING:
                str_builder(tokens[i].value, out);
                break;
            case TOKEN_SEMICOLON:
                strcat(out, ";");
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
    printf("%d\n", tokenCursor);
    process();

    return 0;
}
