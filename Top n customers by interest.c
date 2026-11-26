#include <stdio.h>
void find_top_k_index(int *interest, int n, int k, int *top_k_index);
int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);
    int interest[100];
    for (int i = 0; i < n; i++)
        scanf("%d", &interest[i]);
    int top_k_index[100];
    find_top_k_index(interest, n, k, top_k_index);
    for (int i = 0; i < k; i++)
    {
        if (i > 0) printf(" ");
        printf("%d", top_k_index[i]);
    }
    printf("\n");
    return 0;
}

void find_top_k_index(int *interest, int n, int k, int *top_k_index)
{
    int idx[100];
    for (int i = 0; i < n; i++)
        idx[i] = i;
    for (int i = 0; i < k; i++)
    {
        int max_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (interest[idx[j]] > interest[idx[max_idx]] ||
               (interest[idx[j]] == interest[idx[max_idx]] && idx[j] < idx[max_idx]))
                max_idx = j;
        }
        int temp = idx[i];
        idx[i] = idx[max_idx];
        idx[max_idx] = temp;
    }
    for (int i = 0; i < k; i++)
        top_k_index[i] = idx[i];
}

