#include <stdio.h>
#include <time.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int longestSubseqDP(int arr[], int n)
{
    int dp[n];
    int max_length = 0;

    // Inicializa todos os valores de dp com 1, pois o menor LIS em cada posição é o próprio elemento
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    // Preenche a tabela dp
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }
    }

    // Encontra o comprimento máximo na tabela dp
    for (int i = 0; i < n; i++)
    {
        if (dp[i] > max_length)
        {
            max_length = dp[i];
        }
    }

    return max_length;
}

int main()
{
    int arr[] = {2, 5, 9, 3, 7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 5, 5, 6, 7, 9, 0, 1, 2, 3, 4, 5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,11,1,1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LIS DP\n");
    clock_t t = clock();
    printf("    Length of LIS is %d\n", longestSubseqDP(arr, n));
    t = clock() - t;
    double tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("    Time: %f\n", tempo);
    return 0;
}
