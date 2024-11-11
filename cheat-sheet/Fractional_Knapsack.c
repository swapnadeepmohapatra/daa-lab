// Fractional Knapsack Problem

#include <stdio.h>

typedef struct
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
} ITEM;

void selectionSort(ITEM items[], int n)
{
    int i, j, max_idx;
    for (i = 0; i < n - 1; i++)
    {
        max_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (items[j].profit_weight_ratio > items[max_idx].profit_weight_ratio)
            {
                max_idx = j;
            }
        }
        if (max_idx != i)
        {
            ITEM temp = items[i];
            items[i] = items[max_idx];
            items[max_idx] = temp;
        }
    }
}

float fractionalKnapsack(ITEM items[], int n, float capacity)
{
    float total_profit = 0.0;
    int i;

    for (i = 0; i < n && capacity > 0; i++)
    {
        if (items[i].item_weight <= capacity)
        {
            capacity -= items[i].item_weight;
            total_profit += items[i].item_profit;
            printf("%d %.6f %.6f 1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
        }
        else
        {
            float fraction = capacity / items[i].item_weight;
            total_profit += items[i].item_profit * fraction;
            printf("%d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            capacity = 0;
        }
    }
    return total_profit;
}

int main()
{
    int n, i;
    float capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    ITEM items[n];
    for (i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    selectionSort(items, n);

    printf("\nItem No profit Weight Amount to be taken\n");
    float max_profit = fractionalKnapsack(items, n, capacity);

    printf("Maximum profit: %.6f\n", max_profit);

    return 0;
}
