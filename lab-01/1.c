#include <stdio.h>
#include <stdlib.h>

void findSecondSmallestAndLargest(int arr[], int n, int *secondSmallest, int *secondLargest) {
    if (n < 2) {
        *secondSmallest = -1;
        *secondLargest = -1;
        return;
    }

    int firstSmallest, firstLargest;
    firstSmallest = firstLargest = arr[0];
    *secondSmallest = *secondLargest = -1;

    for (int i = 1; i < n; i++) {
        if (arr[i] < firstSmallest) {
            *secondSmallest = firstSmallest;
            firstSmallest = arr[i];
        } else if (arr[i] > firstSmallest && (*secondSmallest == -1 || arr[i] < *secondSmallest)) {
            *secondSmallest = arr[i];
        }

        if (arr[i] > firstLargest) {
            *secondLargest = firstLargest;
            firstLargest = arr[i];
        } else if (arr[i] < firstLargest && (*secondLargest == -1 || arr[i] > *secondLargest)) {
            *secondLargest = arr[i];
        }
    }
}


int main() {
    const char *filePath = "array.txt";
    int arr[100];
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

    readArrayFromFile(filePath, arr, &n);


    int secondSmallest, secondLargest;
    
    findSecondSmallestAndLargest(arr, n, &secondSmallest, &secondLargest);

    printf("Second smallest element: %d\n", secondSmallest);
    printf("Second largest element: %d\n", secondLargest);


    return 0;
}
