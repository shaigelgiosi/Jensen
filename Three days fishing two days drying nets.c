#include<stdio.h>
#define START_YEAR 1990
#define START_MONTH 1
#define START_DAY 1
int is_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        return 1;
    else
        return 0;
}
int month_days(int year, int month)
{
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && is_leap_year(year))
        return 29;
    else
        return days_in_month[month - 1];
}
int main(void)
{
    int year, month, day;
    int calculate_days;
    long total_days = 0;
    if (scanf("%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        printf("Invalid input");
        return 0;
    }
    if (year < START_YEAR ||
        month < 1 || month > 12 ||
        day < 1 || day > month_days(year, month))
    {
        printf("Invalid input");
        return 0;
    }
    for (int y = START_YEAR; y < year; y++)
    {
        total_days += 365 + is_leap_year(y);
    }
    for (int m = START_MONTH; m < month; m++)
    {
        total_days += month_days(year, m);
    }
    total_days += day - START_DAY;
    calculate_days = total_days % 5;
    if (calculate_days < 3)
    {
        printf("working");
    }
    else
    {
        printf("rest");
    }
    return 0;
}
