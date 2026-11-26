#include <stdio.h>
void sort_interest(int *interest, int n);

int main(void) {
    int n;
    scanf("%d", &n);
    int interest[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    sort_interest(interest, n);
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", interest[i]);
    }
    printf("\n");
    return 0;
}

void sort_interest(int *interest, int n)
{
    for (int i = 0; i < n - 1; i++)          // Outer loop: n-1 passes in total
    {
        for (int j = 0; j < n - 1 - i; j++)  // Inner loop: compare adjacent elements
        {
            if (interest[j] < interest[j + 1])  // Descending order: swap if the previous one is smaller
            {
                int temp = interest[j];
                interest[j] = interest[j + 1];
                interest[j + 1] = temp;
            }
        }
    }
}