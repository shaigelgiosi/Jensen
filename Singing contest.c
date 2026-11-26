#include <stdio.h>
#include <limits.h>
int main(void)
{
    int n, m;
    scanf("%d%d",&n,&m);
    int a[m];
    double average[n];
    for (int i = 0; i < n; i++)
    {
        int min = INT_MAX, max = INT_MIN, sum = 0;
        for (int j = 0; j < m; j++)
        {
            scanf("%d",&a[j]);
            if (max < a[j]) max = a[j];
            if (min > a[j]) min = a[j];
            sum += a[j];
        }
        average[i] = (double)(sum - min - max) / (m - 2);
    }

    double max0 = average[0];
    for (int k = 1; k < n; k++)
        if (average[k] > max0)
            max0 = average[k];

    printf("%.2f\n", max0);
    return 0;
}

