#include "header.h"

extern int processIndex;
extern Token tokens[1024];

Token printProcess[16];
int printProcessIndex;

10 + 20 * 3

void start_print()
{
    if(!expect_next(TOKEN_OPARAN)){return;}
    printProcessIndex = 0;
    processIndex++;
    processIndex++;

    //printProcess[printProcessIndex]

    if(tokens[processIndex].type == TOKEN_ID)
    {

    }
    else if(tokens[processIndex].type == TOKEN_INT)
    {

    }
}
