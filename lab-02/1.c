#include <stdio.h>
#include <stdlib.h>

int decimalToBinary(int num)
{
    if (num == 0)
    {
        return 0;
    }
    else
    {
        return (num % 2 + 10 * decimalToBinary(num / 2));
    }
}

void main(int narg, char *argv[])
{

    FILE *inputFile;
    FILE *outputFile;
    int numOfDigits;

    numOfDigits = (int)atoi(argv[1]);

    int arrayOfNums[numOfDigits];

    inputFile = fopen(argv[2], "r");
    outputFile = fopen(argv[3], "w");

    for (int i = 0; i < numOfDigits; i++)
    {
        fscanf(inputFile, "%d", &arrayOfNums[i]);
    }

    for (int i = 0; i < numOfDigits; i++)
    {
        fprintf(outputFile, "The binary equivalent of %d is : %d\n", arrayOfNums[i], decimalToBinary(arrayOfNums[i]));
    }
}