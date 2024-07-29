#include <stdio.h>
#include <stdlib.h>

int gcd(int num1, int num2)
{
    if (num2 != 0)
    {
        return gcd(num2, num1 % num2);
    }
    else
    {
        return num1;
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

    for (int i = 0; i < numOfDigits; i += 2)
    {
        fprintf(outputFile, "The GCD of %d and %d is : %d\n", arrayOfNums[i], arrayOfNums[i + 1], gcd(arrayOfNums[i], arrayOfNums[i + 1]));
    }
}