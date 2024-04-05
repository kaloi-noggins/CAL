void ordenaInsercao(int *v, int n)
{
    int i, j, x;
    for (i = 0; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}