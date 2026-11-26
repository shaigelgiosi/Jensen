#include <stdio.h>

int removeDuplicates(int arr[], int num)
{
    if (num == 0) {
        return 0;
    }

    int k = 1;
    for (int i = 1; i < num; i++) {
        if (arr[i] != arr[i - 1]) {
            arr[k++] = arr[i];
        }
    }

    return k;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    if(n == 0)
    {
        printf("\n");
        return 0;
    }
    int even_number[1000], odd_number[1000];
    int final_number[1000];
    int num_even = 0, num_odd = 0;

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        if (x % 2 == 0) {
            even_number[num_even++] = x;
        } else {
            odd_number[num_odd++] = x;
        }
    }

    int i = 0, j = 0, k = 0;

    while (i < num_even && j < num_odd) {
        final_number[k++] = even_number[i++];
        final_number[k++] = odd_number[j++];
    }

    while (i < num_even) {
        final_number[k++] = even_number[i++];
    }

    while (j < num_odd) {
        final_number[k++] = odd_number[j++];
    }

    int new_length = removeDuplicates(final_number, k);

    for (int t = 0; t < new_length; t++) {
        if (t > 0) {
            printf(" ");
        }
        printf("%d", final_number[t]);
    }

    return 0;
}