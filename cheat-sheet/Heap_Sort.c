#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i)
{

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
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

    heapSort(arr, n);

    FILE *outputFile = fopen(outputFileName, "w");

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    fclose(outputFile);

    return 0;
}
