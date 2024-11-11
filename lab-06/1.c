// Heap Sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char name[50];
    int age;
    int height;
    int weight;
};

void readData(struct person **students, int *n);
void createMinHeap(struct person *students, int n);
void createMaxHeap(struct person *students, int n);
void heapifyMin(struct person *students, int n, int i);
void heapifyMax(struct person *students, int n, int i);
void displayWeightOfYoungest(struct person *students, int n);
void insertIntoMinHeap(struct person **students, int *n);
void deleteOldest(struct person *students, int *n);
void swap(struct person *a, struct person *b);

int main()
{
    struct person *students = NULL;
    int n = 0;
    int option;

    while (option != 7)
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            readData(&students, &n);
            break;
        case 2:
            createMinHeap(students, n);
            printf("Min-heap created based on age.\n");
            break;
        case 3:
            createMaxHeap(students, n);
            printf("Max-heap created based on weight.\n");
            break;
        case 4:
            displayWeightOfYoungest(students, n);
            break;
        case 5:
            insertIntoMinHeap(&students, &n);
            break;
        case 6:
            deleteOldest(students, &n);
            break;
        case 7:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option! Please try again.\n");
            break;
        }
    }

    free(students);

    return 0;
}

void readData(struct person **students, int *n)
{
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    fscanf(file, "%d", n);
    *students = (struct person *)malloc(*n * sizeof(struct person));

    for (int i = 0; i < *n; i++)
    {
        fscanf(file, "%d %s %d %d %d", &(*students)[i].id, (*students)[i].name, &(*students)[i].age,
               &(*students)[i].height, &(*students)[i].weight);
    }

    fclose(file);
    printf("Data successfully read from file.\n");
}

void createMinHeap(struct person *students, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapifyMin(students, n, i);
    }
}

void heapifyMin(struct person *students, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && students[left].age < students[smallest].age)
        smallest = left;

    if (right < n && students[right].age < students[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&students[i], &students[smallest]);
        heapifyMin(students, n, smallest);
    }
}

void createMaxHeap(struct person *students, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapifyMax(students, n, i);
    }
}

void heapifyMax(struct person *students, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && students[left].weight > students[largest].weight)
        largest = left;

    if (right < n && students[right].weight > students[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&students[i], &students[largest]);
        heapifyMax(students, n, largest);
    }
}

void displayWeightOfYoungest(struct person *students, int n)
{
    if (n == 0)
    {
        printf("No data available.\n");
        return;
    }

    createMinHeap(students, n);
    double weightInKg = students[0].weight * 0.453592;
    printf("Weight of the youngest person: %.2f kg\n", weightInKg);
}

void insertIntoMinHeap(struct person **students, int *n)
{
    *students = (struct person *)realloc(*students, (*n + 1) * sizeof(struct person));

    printf("Enter ID, Name, Age, Height, Weight (in pounds):\n");
    scanf("%d %s %d %d %d", &(*students)[*n].id, (*students)[*n].name, &(*students)[*n].age,
          &(*students)[*n].height, &(*students)[*n].weight);

    (*n)++;
    createMinHeap(*students, *n);
    printf("New person added and min-heap updated.\n");
}

void deleteOldest(struct person *students, int *n)
{
    if (*n == 0)
    {
        printf("No data available.\n");
        return;
    }

    createMaxHeap(students, *n);
    printf("Deleted person: ID=%d, Name=%s, Age=%d, Height=%d, Weight=%d lbs\n",
           students[0].id, students[0].name, students[0].age, students[0].height, students[0].weight);

    students[0] = students[*n - 1];
    (*n)--;
    heapifyMax(students, *n, 0);
}

void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}
