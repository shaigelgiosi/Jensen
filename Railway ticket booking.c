#include <stdio.h>

typedef struct {
    int num;      
    char word;
    int sold;     
} Point;

int main(void)
{
    int times;
    scanf("%d", &times);
    Point a[20][5];
    char word[5] = {'A', 'B', 'C', 'D', 'F'};

    for (int r = 0; r < 20; r++) {
        for (int c = 0; c < 5; c++) {
            a[r][c].num = r + 1;
            a[r][c].word = word[c];
            a[r][c].sold = 0;
        }
    }

    for (int t = 0; t < times; t++) {
        int p;
        scanf("%d", &p);

        int row = -1;
        int start = -1;

        for (int r = 0; r < 20 && row == -1; r++) {
            for (int c = 0; c + p <= 5; c++) {
                int available = 1;

                for (int j = 0; j < p; j++) {
                    if (a[r][c + j].sold == 1) {
                        available = 0;
                        break;
                    }
                }

                if (available == 1) {
                    row = r;
                    start = c;
                    break;
                }
            }
        }

        if (row != -1) {
            for (int j = 0; j < p; j++) {
                int c = start + j;
                a[row][c].sold = 1;

                if (j > 0) {
                    printf(" ");
                }
                printf("%d%c", a[row][c].num, a[row][c].word);
            }
        } else {
            int count = 0;

            for (int r = 0; r < 20 && count < p; r++) {
                for (int c = 0; c < 5 && count < p; c++) {
                    if (a[r][c].sold == 0) {
                        a[r][c].sold = 1;

                        if (count > 0) {
                            printf(" ");
                        }
                        printf("%d%c", a[r][c].num, a[r][c].word);
                        count++;
                    }
                }
            }
        }

        printf("\n");
    }

    return 0;
}