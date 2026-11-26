#include<stdio.h>
int hanoi(int num, char a, char b, char c)
{
    if(num == 0)
    {
        return 0;
    }
    else
    {
        hanoi(num - 1, a, c, b);
        printf("Move disk from %c to %c\n", a, c);
        hanoi(num - 1, b, a, c);
    }
}
int main(void)
{
    int n;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}
