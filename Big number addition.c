#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[100];
    char str2[100];
    while (scanf("%s %s", str1, str2) != EOF) {
        int num1[100] = {0};
        int num2[100] = {0};
        int result[105] = {0};
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        for (int i = 0; i < len1; i++) {
            num1[i] = str1[len1 - 1 - i] - '0';
        }
        for (int i = 0; i < len2; i++) {
            num2[i] = str2[len2 - 1 - i] - '0';
        }
        int max_len = (len1 > len2) ? len1 : len2;
        int carry = 0;
        for (int i = 0; i < max_len; i++) {
            int sum = num1[i] + num2[i] + carry;
            result[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry > 0) {
            result[max_len] = carry;
            max_len++;
        }
        for (int i = max_len - 1; i >= 0; i--) {
            printf("%d", result[i]);
        }
    }

    return 0;
}

