#include "header.h"

Token tokens[1024];
int tokenCursor = 0;
extern char* keywords[KEYWORD_COUNT];
extern int processIndex;

void tokenize(FD *file)
{
    char tokenBuf[1024];
    int tokenBufCursor = 0;
    memset(tokenBuf, 0, (strlen(tokenBuf) + 1) * sizeof(char));

        if(file->buf[file->index] == '\n' || file->buf[file->index] == '\n' || file->buf[file->index] == ' ')
      {

      }
      else
      {
          if(file->buf[file->index] == '#'){for(;file->buf[file->index] !='\n'; file->index++){}}
          if(file->buf[file->index] == '"')
          {
              tokenBuf[tokenBufCursor] = 34;
              tokenBufCursor++;
              file->index++;
              for(; '"' != file->buf[file->index]; file->index++)
              {
                  tokenBuf[tokenBufCursor] = file->buf[file->index];
                  tokenBufCursor++;
              }
              tokenBuf[tokenBufCursor] = 34;
              tokenBufCursor++;
              //strcpy(tokens[tokenCursor].value, tokenBuf);
              memcpy(tokens[tokenCursor].value, tokenBuf, sizeof(char) * (tokenBufCursor));
              tokens[tokenCursor].type = TOKEN_STRING;
              tokenBufCursor = 0;
              tokenCursor++;
          }
          else if(isalpha(file->buf[file->index]))
          {
              for(tokenBufCursor = 0; 0 != isalnum(file->buf[file->index]); file->index++)
              {
                  tokenBuf[tokenBufCursor] = file->buf[file->index];
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
                  }
                  else
                  {
                      tokens[tokenCursor].type = TOKEN_ID;
                  }
              }
              memcpy(tokens[tokenCursor].value, tokenBuf, sizeof(char) * (tokenBufCursor));
              //strcpy(tokens[tokenCursor].value, tokenBuf);
              tokenBufCursor = 0;
              tokenCursor++;
          }
          else if(isdigit(file->buf[file->index]))
          {
              for(tokenBufCursor = 0; 0 != isdigit(file->buf[file->index]); file->index++)
              {
                  tokenBuf[tokenBufCursor] = file->buf[file->index];
                  tokenBufCursor++;
              }
              memcpy(tokens[tokenCursor].value, tokenBuf, sizeof(char) * (tokenBufCursor));
              tokens[tokenCursor].data = (int*)numberizer(tokens[tokenCursor].value);
              printf("Data put: %p\n", tokens[tokenCursor].data);
              tokens[tokenCursor].type = TOKEN_INT;
              tokenBufCursor = 0;
              tokenCursor++;
          }
          switch(file->buf[file->index])
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
              case '+':
                  strcpy(tokens[tokenCursor].value, "+");
                  tokens[tokenCursor].type = TOKEN_PLUS;
                  tokenCursor++;
                  break;
          }
      }
}

void print_tokens()
{
    for(int l = 0; l < tokenCursor ; l++)
    {
        printf("Tokens: %s\n", tokens[l].value);
    }
}

int expect_next(TokenType type)
{
    if(tokens[processIndex + 1].type == type) return 1;
    else return 0;
}

int expect_cornered(TokenType type)
{
    printf("type at -1:%d | type at 1:%d\n",tokens[processIndex - 1].type, tokens[processIndex + 1].type);
    if(tokens[processIndex - 1].type == type && tokens[processIndex + 1].type == type) return 1;
    else return 0;
}

int numberizer(char* numberAsString)
{
    int total;
    int temp;
    printf("given string: %s - ", numberAsString);
    for(int i = 0; numberAsString[i] != '\0'; i++)
    {
        temp = ((int)numberAsString[i] - 48) * pow(10, i);
        total += temp;
    }
    printf("end result: %d\n", total);
    return total;
}
