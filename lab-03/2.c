#include <stdio.h>
#include <stdlib.h>

int comparisonCount = 0;

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            comparisonCount++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        comparisonCount++;
        arr[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];

    int n = atoi(argv[3]);

    FILE *inputFile = fopen(inputFileName, "r");

    int arr[n];

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fclose(inputFile);

    comparisonCount = 0;

    insertionSort(arr, n);

    FILE *outputFile = fopen(outputFileName, "w");
    
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", arr[i]);
    }
    fprintf(outputFile, "\n");
    fprintf(outputFile, "Number of comparisons: %d\n", comparisonCount);

    fclose(outputFile);

    return 0;
}
