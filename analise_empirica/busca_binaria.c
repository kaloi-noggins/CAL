#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int busca_binaria(int v[], int esq, int dir, int elem)
{
    while (esq <= dir)
    {
        int pivo = esq + (dir - esq) / 2;
        if (v[pivo] == elem)
        {
            return pivo;
        }
        if (v[pivo] < elem)
        {
            esq = pivo + 1;
        }
        else
        {
            dir = pivo - 1;
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
    int index = busca_binaria(v, 0,size-1, elem); // timestamp final da contagem
    t = clock() - t;
    double tempo = ((double)t) / CLOCKS_PER_SEC;
    printf("%f", tempo);
    return 0;
}