#include "header.h"

int processIndex;
extern Token tokens[1024];
extern int tokenCursor;

int process(FD *inFile, FD *outFile)
{
    strcat(outFile->buf,"#include <stdio.h>\nint main(){\n");

    for(processIndex = 0; processIndex < tokenCursor; processIndex++)
    {
        switch(tokens[processIndex].type)
        {
            case TOKEN_ID:
                printf("Was Here as %s\n", tokens[processIndex].value);
                strcat(outFile->buf, tokens[processIndex].value);
                break;
            case TOKEN_TYPE_CHAA:
                strcat(outFile->buf, "char* ");
                if(!expect_next(TOKEN_ID)){printf("problem in process chaa\n"); break;}
                //tokens[processIndex + 1].type = TOKEN_TYPE_CHAA;
                processIndex++;
                strcat(outFile->buf, tokens[processIndex].value);
                break;
            case TOKEN_TYPE_INT:
                strcat(outFile->buf, "int ");
                if(!expect_next(TOKEN_ID)){printf("problem in process int\n"); break;}
                //tokens[processIndex + 1].type = TOKEN_TYPE_INT;
                processIndex++;
                strcat(outFile->buf, tokens[processIndex].value);
                break;
            case TOKEN_PRINT:
                #ifdef _WIN64
                    strcat(outFile->buf, "puts");
                    //start_print();
                #elif __linux__
                    strcat(outFile->buf, "echo");
                #endif
                break;
            case TOKEN_OPARAN:
                strcat(outFile->buf, "(");
                break;
            case TOKEN_CPARAN:
                strcat(outFile->buf, ")");
                break;
            case TOKEN_STRING:
                strcat(outFile->buf, tokens[processIndex].value);
                //str_builder(tokens[i].value, out);
                break;
            case TOKEN_INT:
                printf("pointer: %p\n", tokens[processIndex].data);
                printf("Here as an Int: %d\n", *(int*)(tokens[processIndex].data));
                strcat(outFile->buf, tokens[processIndex].value);
                break;
            case TOKEN_SEMICOLON:
                strcat(outFile->buf, ";\n");
                break;
            case TOKEN_PLUS:
                strcat(outFile->buf, " + ");
                break;
                int plusInt;
                if(expect_cornered(TOKEN_INT))
                {
                    char plusStr[2048];
                    sprintf(plusStr, "%d", plusInt);
                    strcat(outFile->buf, plusStr);
                    sprintf(plusStr, "- %s", tokens[processIndex - 1].value);
                    strcat(outFile->buf, plusStr);
                    processIndex++;
                }
                else if(expect_cornered(TOKEN_ID))
                {
                    plusInt = *(int*)(tokens[processIndex - 1].data);
                    printf("Plus Sum: %d\n",plusInt);
                }
                else printf("problem in token_plus\n");
                break;
            case TOKEN_EQUALS:
                strcat(outFile->buf, "=");
                char equalStr[2048];
                switch(tokens[processIndex - 1].type)
                {
                    case TOKEN_TYPE_INT:
                        tokens[processIndex - 1].data;
                        break;
                    case TOKEN_TYPE_CHAA:
                        tokens[processIndex - 1].data = (tokens[processIndex + 1].value);
                        break;
                }
                //processIndex++;
                break;
            }
        }
    strcat(outFile->buf," return 0;}");
    printf("pro: %d | token: %d\n",processIndex, tokenCursor);
    fprintf(outFile->file, "%s\n", outFile->buf);
    fclose(outFile->file);
}
