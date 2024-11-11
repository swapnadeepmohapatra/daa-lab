#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find and print the LCS
void find_lcs(char *X, char *Y)
{
    int m = strlen(X);
    int n = strlen(Y);
    int L[m + 1][n + 1];

    // Build the LCS table in bottom-up fashion
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                L[i][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1])
            {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            else
            {
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
            }
        }
    }

    // Length of LCS is L[m][n]
    printf("LCS Length: %d\n", L[m][n]);

    // Recover the LCS from the LCS table
    int index = L[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("LCS: %s\n", lcs);
}

int main()
{
    char X[100], Y[100];
    printf("Enter the first string into an array: ");
    scanf("%s", X);
    printf("Enter the second string into an array: ");
    scanf("%s", Y);

    find_lcs(X, Y);
    return 0;
}
