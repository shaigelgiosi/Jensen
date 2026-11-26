#include <stdio.h>
int main(void)
{
    int result, num;
    char op;
    if (scanf("%d", &result) != 1) 
    {
        return 0;
    }
    while ((op = getchar()) != '=') {
        if (op != '+' && op != '-' && op != '*' && op != '/') 
        {
            printf("Invalid operator: %c\n", op);
            return 0;
        }
        scanf("%d", &num);
        switch (op) {
        case '+': result += num; break;
        case '-': result -= num; break;
        case '*': result *= num; break;
        case '/': result /= num; break;
        }
    }
    printf("%d\n", result);
    return 0;
}