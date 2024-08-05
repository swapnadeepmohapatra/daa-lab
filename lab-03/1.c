#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisonCount = 0;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        comparisonCount++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
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

    clock_t start, end;
    double cpu_time_used;

    comparisonCount = 0;
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    FILE *outputFile = fopen(outputFileName, "w");
    
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }
    printf("Number of comparisons: %d\n", comparisonCount);
    printf("Time taken to sort the array: %f seconds\n", cpu_time_used);

    fclose(outputFile);

    return 0;
}
