#include <stdio.h>
long long sumFactors(long long x)
{
    long long sum = 0;

    for (long long i = 1; i <= x / 2; i++)
    {
        if (x % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}
int main(void)
{
    long long n;
    scanf("%lld", &n);

    for (long long a = 1; a <= n; a++)
    {
        long long b = sumFactors(a);

        if (b > a && b <= n && sumFactors(b) == a)
        {
            printf("(%lld,%lld)\n", a, b);
        }
    }
    return 0;
}
