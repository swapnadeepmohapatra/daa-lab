#include <stdio.h>
#include <limits.h>

// Function to print optimal parenthesization
void print_optimal_parens(int i, int j, int s[][j + 1], char *name)
{
    if (i == j)
    {
        printf("%c", (*name)++);
    }
    else
    {
        printf("(");
        print_optimal_parens(i, s[i][j], s, name);
        print_optimal_parens(s[i][j] + 1, j, s, name);
        printf(")");
    }
}

// Function to implement matrix chain multiplication using M and S tables
void matrix_chain_order(int p[], int n)
{
    int M[n][n]; // M table to store the number of scalar multiplications
    int S[n][n]; // S table to store the optimal split points

    // Initialize the main diagonal of M to zero since single matrices need no multiplication
    for (int i = 1; i < n; i++)
    {
        M[i][i] = 0;
    }

    // Calculate number of multiplications in a bottom-up manner
    for (int chain_len = 2; chain_len < n; chain_len++)
    {
        for (int i = 1; i < n - chain_len + 1; i++)
        {
            int j = i + chain_len - 1;
            M[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int q = M[i][k] + M[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < M[i][j])
                {
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }

    // Print M table
    printf("M Table:\n");
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i > j)
            {
                printf("    ");
            }
            else
            {
                printf("%4d ", M[i][j]);
            }
        }
        printf("\n");
    }

    // Print S table
    printf("S Table:\n");
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i >= j)
            {
                printf("    ");
            }
            else
            {
                printf("%4d ", S[i][j]);
            }
        }
        printf("\n");
    }

    // Print the optimal parenthesization
    char name = 'A';
    printf("Optimal parenthesization: ");
    print_optimal_parens(1, n - 1, S, &name);
    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", M[1][n - 1]);
}

int main()
{
    int num_matrices;
    printf("Enter number of matrices: ");
    scanf("%d", &num_matrices);

    int p[num_matrices + 1];
    printf("Enter row and col size of each matrix:\n");
    for (int i = 1; i <= num_matrices; i++)
    {
        int row, col;
        printf("Enter row and col size of A%d: ", i);
        scanf("%d %d", &row, &col);

        // Set dimensions in array p
        if (i == 1)
        {
            p[0] = row;
        }
        p[i] = col;

        // Validate dimension compatibility
        if (i > 1 && p[i - 1] != row)
        {
            printf("Error: Matrix dimensions are incompatible for multiplication.\n");
            return 1;
        }
    }

    matrix_chain_order(p, num_matrices + 1);
    return 0;
}
