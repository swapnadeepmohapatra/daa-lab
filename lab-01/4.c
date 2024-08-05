#include <stdio.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *p1, int p2) {
    if (p2 <= 1) {
        return;
    }
    
    int lastElement = *(p1 + p2 - 1);

    for (int i = p2 - 1; i > 0; i--) {
        EXCHANGE(p1 + i, p1 + i - 1);
    }

    *p1 = lastElement;
}

int main() {
    int N = 9;
    int arr[N];
    int p2;

    printf("Enter %d elements of the array: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of elements to rotate: ");
    scanf("%d", &p2);

    printf("Before ROTATE: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    ROTATE_RIGHT(arr, p2);

    printf("After ROTATE:  ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
