#include <stdio.h>
#include <stdlib.h>


int findTotalDuplicates(int arr[], int n) {
    int totalDuplicates = 0;
    int counted[n]; 

    for (int i = 0; i < n; i++) {
        counted[i] = 0; 
    }

    for (int i = 0; i < n; i++) {
        if (counted[i] == 1) {
            continue;
        }
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > 1) {
            totalDuplicates += count - 1; 
        }
        counted[i] = 1;
    }

    return totalDuplicates;
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

int main() {
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

    return 0;
}
