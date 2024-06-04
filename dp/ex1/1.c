#include <stdio.h>
#include <time.h>
void printSp(int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        printf("  ");
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int LongestSubSeq(int arr[], int i, int n, int prev)
{
    // printSp(i);
    // printf("CALL: %d / %d: \n", i, prev);

    // Caso base: se todos os elementos foram processados
    if (i == n)
    {
        // printSp(i);
        // printf("0\n");
        return 0;
    }

    // Caso 1: Exclui o elemento atual e processa os elementos restantes
    int excl = LongestSubSeq(arr, i + 1, n, prev);

    // Caso 2: Inclui o elemento atual se for maior que o elemento anterior na LIS
    int incl = 0;
    if (arr[i] > prev)
    {
        incl = 1 + LongestSubSeq(arr, i + 1, n, arr[i]);
    }

    // Retorna o máximo das duas opções acima
    // printSp(i);
    // printf("%d\n", max(incl, excl));
    return max(incl, excl);
}

int main()
{
    // int arr[] = {2, 5, 9, 3, 7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 5, 5, 6, 7, 9, 0, 1, 2, 3, 4, 5};
    int arr[] = {2, 5, 9, 3, 7, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 5, 5, 6, 7, 9, 0, 1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LIS\n");
    clock_t t = clock();
    printf("    Length of LIS is %d\n", LongestSubSeq(arr, 0, n, -1000000)); // Usa um valor muito pequeno como "prev" inicial
    t = clock() - t;
    double tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("    Time: %f\n", tempo);
    return 0;
}
