#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[])
{
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];

    int n = atoi(argv[3]);

    FILE *inputFile = fopen(inputFileName, "r");

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fclose(inputFile);

    quickSort(arr, 0, n - 1);

    FILE *outputFile = fopen(outputFileName, "w");

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    fclose(outputFile);

    return 0;
}
