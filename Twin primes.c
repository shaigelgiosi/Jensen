#include <stdio.h>
void brother(int n, int low, int high)
{
    if(low + 2 > high)
    {
        printf("\n");
        printf("0");
        return;
    }
    for (int i = low; i <= high; i++)
    {
        int mid = i + 2;
        int flag = 1;
        for (int j = 2; j <= mid / j; j++)
        {
            if ((j < i && i % j == 0) || mid % j == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag){
             printf("(%d,%d)", i, mid);
             n++;
        }
    }
    printf("\n");
    printf("%d",n);
}
int main(void)
{
    int c, d;
    int num = 0;
    scanf("%d,%d", &c, &d);
    brother(num, c, d);
    return 0;
}
