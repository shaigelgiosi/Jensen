#include <stdio.h>
#include <string.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    int a[1000];
    int cnt[4] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        cnt[a[i]]++;
    }
    int mis[4][4];
    memset(mis, 0, sizeof(mis));
    for (int i = 0; i < n; i++)
    {
        int target;
        if (i < cnt[1])
            target = 1;
        else if (i < cnt[1] + cnt[2])
            target = 2;
        else
            target = 3;

        if (a[i] != target)
            mis[target][a[i]]++;
    }
    int swaps = 0;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = i + 1; j <= 3; j++)
        {
            int t = mis[i][j] < mis[j][i] ? mis[i][j] : mis[j][i];
            swaps += t;
            mis[i][j] -= t;
            mis[j][i] -= t;
        }
    }
    int remaining = mis[1][2] + mis[1][3] + mis[2][1] + mis[2][3] + mis[3][1] + mis[3][2];
    swaps += remaining / 3 * 2;
    printf("%d\n", swaps);
    return 0;
}

