#include <stdio.h>
#include <stdlib.h>

typedef struct SYMBOL
{
    char alphabet;
    int frequency;
} SYMBOL;

typedef struct Node
{
    SYMBOL symbol;
    struct Node *left, *right;
} Node;

Node *createNode(char alphabet, int frequency)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->symbol.alphabet = alphabet;
    newNode->symbol.frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertMinHeap(Node *heap[], int *heapSize, Node *newNode)
{
    heap[*heapSize] = newNode;
    int i = *heapSize;
    (*heapSize)++;

    while (i > 0 && heap[(i - 1) / 2]->symbol.frequency > heap[i]->symbol.frequency)
    {
        Node *temp = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = heap[i];
        heap[i] = temp;
        i = (i - 1) / 2;
    }
}

Node *extractMin(Node *heap[], int *heapSize)
{
    if (*heapSize == 0)
        return NULL;

    Node *minNode = heap[0];
    heap[0] = heap[*heapSize - 1];
    (*heapSize)--;

    int i = 0;
    while (2 * i + 1 < *heapSize)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < *heapSize && heap[left]->symbol.frequency < heap[smallest]->symbol.frequency)
            smallest = left;
        if (right < *heapSize && heap[right]->symbol.frequency < heap[smallest]->symbol.frequency)
            smallest = right;
        if (smallest != i)
        {
            Node *temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        }
        else
        {
            break;
        }
    }

    return minNode;
}

Node *buildHuffmanTree(SYMBOL symbols[], int n)
{
    Node *minHeap[100];
    int heapSize = 0;

    for (int i = 0; i < n; i++)
    {
        insertMinHeap(minHeap, &heapSize, createNode(symbols[i].alphabet, symbols[i].frequency));
    }

    while (heapSize > 1)
    {
        Node *left = extractMin(minHeap, &heapSize);
        Node *right = extractMin(minHeap, &heapSize);

        Node *newNode = createNode('$', left->symbol.frequency + right->symbol.frequency);
        newNode->left = left;
        newNode->right = right;

        insertMinHeap(minHeap, &heapSize, newNode);
    }

    return extractMin(minHeap, &heapSize);
}

void inOrderTraversal(Node *root)
{
    if (root == NULL)
        return;

    inOrderTraversal(root->left);
    if (root->symbol.alphabet != '$')
    {
        printf("%c ", root->symbol.alphabet);
    }
    inOrderTraversal(root->right);
}

int main()
{
    int n;

    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    SYMBOL symbols[n];
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &symbols[i].frequency);
    }

    Node *root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
