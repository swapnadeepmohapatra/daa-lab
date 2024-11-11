#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char firstName[100];
    char lastName[100];
    int age;
    int height;
    int weight;
};

void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyWeight(struct person arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapifyWeight(arr, n, largest);
    }
}

void heapifyAge(struct person arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        heapifyAge(arr, n, smallest);
    }
}

void buildMaxHeap(struct person arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyWeight(arr, n, i);
}

void buildMinHeap(struct person arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyAge(arr, n, i);
}

void insertPerson(struct person arr[], int *n, struct person newPerson)
{
    (*n)++;
    arr[*n - 1] = newPerson;

    int i = *n - 1;
    while (i != 0 && arr[(i - 1) / 2].age > arr[i].age)
    {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteOldestPerson(struct person arr[], int *n)
{
    arr[0] = arr[*n - 1];
    (*n)--;

    heapifyAge(arr, *n, 0);
}

void displayWeightOfYoungest(struct person arr[], int n)
{
    buildMinHeap(arr, n);

    printf("Weight of the youngest person: %d\n", arr[0].weight);
}

void printMenu()
{
    printf("\n\n----------------------------\n\n");
    printf("MAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");
}

void printPersons(struct person arr[], int n)
{
    printf("\n----------------------------\n\n");
    printf("ID FirstName LastName Age Height Weight\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d %s %s %d %d %d\n", arr[i].id, arr[i].firstName, arr[i].lastName, arr[i].age, arr[i].height, arr[i].weight);
    }
}

void main(int argc, char *argv[])
{
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];
    int n = atoi(argv[3]);

    FILE *inputFile = fopen(inputFileName, "r");

    struct person *arr = (struct person *)malloc(n * sizeof(struct person));

    for (int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d %s %s %d %d %d", &arr[i].id, arr[i].firstName, arr[i].lastName, &arr[i].age, &arr[i].height, &arr[i].weight);
    }

    fclose(inputFile);

    printMenu();

    int choice;
    scanf("%d", &choice);

    while (choice != 7)
    {
        switch (choice)
        {
        case 1:
            printPersons(arr, n);
            break;
        case 2:
            buildMinHeap(arr, n);
            break;
        case 3:
            buildMaxHeap(arr, n);
            break;
        case 4:
            displayWeightOfYoungest(arr, n);
            break;
        case 5:
        {
            struct person newPerson;
            printf("Enter new person details (Id FirstName LastName Age Height Weight):\n");
            scanf("%d %s %s %d %d %d", &newPerson.id, newPerson.firstName, newPerson.lastName, &newPerson.age, &newPerson.height, &newPerson.weight);
            arr = realloc(arr, (n + 1) * sizeof(struct person));
            insertPerson(arr, &n, newPerson);
            break;
        }
        case 6:
            deleteOldestPerson(arr, &n);
            break;
        default:
            break;
        }

        printMenu();
        scanf("%d", &choice);
    }

    FILE *outputFile = fopen(outputFileName, "w");

    fprintf(outputFile, "ID FirstName LastName Age Height Weight\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d %s %s %d %d %d\n", arr[i].id, arr[i].firstName, arr[i].lastName, arr[i].age, arr[i].height, arr[i].weight);
    }

    fclose(outputFile);
}
