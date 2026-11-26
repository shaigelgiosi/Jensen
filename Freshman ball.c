#include <stdio.h>
#include <string.h>
typedef struct {
    char name[21];
    char id[15];
    char sex;
} FRESHMAN;
int find_student(FRESHMAN stu[], int n, char target[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(stu[i].name, target) == 0 || strcmp(stu[i].id, target) == 0) {
            return i;
        }
    }
    return -1;
}
int main(void) {
    int n, m;
    scanf("%d", &n);
    FRESHMAN students[1005];
    for (int i = 0; i < n; i++) {
        scanf("%s %s %c", students[i].name, students[i].id, &students[i].sex);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char q1[21], q2[21];
        scanf("%s %s", q1, q2);
        
        int idx1 = find_student(students, n, q1);
        int idx2 = find_student(students, n, q2);
        if (idx1 != -1 && idx2 != -1) {
            if (students[idx1].sex != students[idx2].sex) {
                printf("Y\n");
            } else {
                printf("N\n");
            }
        }
    }
    return 0;
}

