#include <stdio.h>
#include <stdlib.h>


int findTotalDuplicates(int arr[], int n) {
    int maxCount = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
        }
    }

    return maxCount;
}

int findMostRepeatingElement(int arr[], int n) {
    int mostRepeatingElement = arr[0];
    int maxCount = 0;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostRepeatingElement = arr[i];
        }
    }

    return mostRepeatingElement;
}

void main() {
    const char *filePath = "array.txt";
    int arr[100];
    int prefixSum[100];
    int n;

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        n = 0;
        return;
    }

    int i = 0;
    while (fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }
    n = i;

    fclose(file);

    int totalDuplicates = findTotalDuplicates(arr, n);
    int mostRepeatingElement = findMostRepeatingElement(arr, n);

    printf("Total number of duplicate elements: %d\n", totalDuplicates);
    printf("Most repeating element: %d\n", mostRepeatingElement);
}
