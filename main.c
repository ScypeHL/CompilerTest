#include "header.h"

FD *inputFile;
FD *outputFile;

char* keywords[KEYWORD_COUNT];

int main(int argc, char const *argv[])
{
    inputFile = malloc(sizeof(FD));
    outputFile = malloc(sizeof(FD));

    //if (argc < 2){printf("Deposit a file to compile!\n"); return 1;}
    //argv[1]

    keywords[0] = "print";
    keywords[1] = "chaa";
    keywords[2] = "int";

    inputFile->file = fopen("test.rpt", "r");
    outputFile->file = fopen("out.c", "w");
    if (!inputFile->file) {printf("File could not found\n"); return 1;}

    fseek(inputFile->file, 0 , SEEK_END);
    inputFile->size = ftell(inputFile->file);
    fseek(inputFile->file, 0 , SEEK_SET);

    printf("No of chars: %lld\n", fread(inputFile->buf, sizeof(char), inputFile->size, inputFile->file));

    for(inputFile->index = 0; inputFile->index < inputFile->size; inputFile->index++)
    {
        tokenize(inputFile);
    }
    print_tokens();

    printf("Processing Time!\n");
    if(process(inputFile, outputFile)){exit(31);}

    free(inputFile);
    free(outputFile);
    return 0;
}
