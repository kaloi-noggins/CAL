#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int busca_sequencial(int v[], int n, int elem)
{
    for (size_t i = 0; i < n; i++)
    {
        if (v[i] == elem)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int size;
    scanf("%d", &size);
    int *v = malloc(size * (sizeof(int)));
    for (size_t i = 0; i < size; i++)
    {
        v[i] = i;
    }
    int elem = v[size-1];
    // timestamp inicio da contagem
    clock_t t = clock();
    int index = busca_sequencial(v, size, elem); // timestamp final da contagem
    t = clock() - t;
    double tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("%f", tempo);
    return 0;
}
