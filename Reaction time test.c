#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>    // Sleep(), GetTickCount()
#else
#include <unistd.h>     // sleep()
#include <sys/time.h>   // gettimeofday()
#endif

#define MAX_RECORDS 100
#define SCORE_FILE  "score.txt"

/* One score record */
typedef struct
{
    char name[20];      // Name (no spaces)
    int  ms;            // Reaction time in milliseconds
    char date[11];      // Date string: YYYY-MM-DD (10+1)
    char time_str[9];   // Time string: HH:MM:SS (8+1)
} Record;

/* Function declarations */
void clear_input_buffer(void);
int  load_records(Record rec[], int max_count);
void show_records(const Record rec[], int count);
int  play_game(void);
int  add_record(Record rec[], int *count, int ms);
void wait_random_seconds(int min_s, int max_s);
double get_current_time_ms(void);

int main(void)
{
    Record records[MAX_RECORDS];
    int count;
    int choice;

    srand((unsigned int)time(NULL));

    // 1. Load previous scores from score.txt at startup
    count = load_records(records, MAX_RECORDS);
    printf("Loaded %d records from %s.\n\n", count, SCORE_FILE);

    // 2. Menu loop
    while (1)
    {
        printf("---------- Reaction Time Test ----------\n");
        printf("1. Start game\n");
        printf("2. Show records\n");
        printf("0. Quit\n");
        printf("Please choose: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input, please try again.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();   // Consume the newline left after the menu choice

        if (choice == 0)
        {
            printf("Bye.\n");
            break;
        }

        if (choice == 1)
        {
            int ms = play_game();
            if (ms < 0)
            {
                printf("Game failed, please try again.\n");
                continue;
            }

            printf("Save this record? (y/n): ");
            int ch = getchar();
            clear_input_buffer();

            if (ch == 'y' || ch == 'Y')
            {
                if (add_record(records, &count, ms) == 1)
                    printf("Record saved.\n");
                else
                    printf("Failed to save record.\n");
            }
        }
        else if (choice == 2)
        {
            show_records(records, count);
        }
        else
        {
            printf("Invalid choice, please try again.\n");
        }

        printf("\n");
    }

    return 0;
}

/* Clear the input buffer */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Wait a random number of seconds between min_s and max_s */
void wait_random_seconds(int min_s, int max_s)
{
    int delay = rand() % (max_s - min_s + 1) + min_s;
#ifdef _WIN32
    Sleep(delay * 1000);
#else
    sleep(delay);
#endif
}

/* Get the current time in milliseconds */
double get_current_time_ms(void)
{
#ifdef _WIN32
    return (double)GetTickCount();
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
#endif
}

/* One round: random wait + timing */
int play_game(void)
{
    int ch;
    
    printf("\n(Waiting randomly, please do NOT press anything...)\n");
    wait_random_seconds(1, 3);

    printf("Now press Enter!\n");
    fflush(stdout);

    // [FIXED] Removed the redundant clear_input_buffer() call that used to be here.

    // Start timing
    double start = get_current_time_ms();

    // Wait for the player to press Enter
    while ((ch = getchar()) != '\n' && ch != EOF) { }

    // Stop timing
    double end = get_current_time_ms();

    double elapsed_ms = end - start;
    printf("Your reaction time: %.0f ms.\n", elapsed_ms);

    if (elapsed_ms < 0) {
        return -1;
    }
    return (int)(elapsed_ms + 0.5);  // Round to the nearest integer
}

/* Load records from file */
int load_records(Record rec[], int max_count)
{
    int count = 0;
    FILE *fp = fopen(SCORE_FILE, "r");
    if(fp == NULL)
    {
        return 0;
    }
    
    while (count < max_count)
    {
        int ret = fscanf(fp, "%19s %d %10s %8s",
                         rec[count].name,
                         &rec[count].ms,
                         rec[count].date,
                         rec[count].time_str);
        if (ret == 4)
        {
            count++;
        }
        else
        {
            break;
        }
    }
    fclose(fp);
    return count;
}

/* Display records */
void show_records(const Record rec[], int count)
{
    if (count == 0)
    {
        printf("No records found.\n");
        return;
    }
    printf("\n%-5s %-15s %-15s %-20s\n", "No.", "Name", "Time(ms)", "Date & Time");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        char datetime[20];
        sprintf(datetime, "%s %s", rec[i].date, rec[i].time_str);
        printf("%-5d %-15s %-15d %-20s\n",
               i + 1,
               rec[i].name,
               rec[i].ms,
               datetime);
    }
}

/* Append a record */
int add_record(Record rec[], int *count, int ms)
{
    if (*count >= MAX_RECORDS)
    {
        printf("Record array is full!\n");
        return -1;
    }
    
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int idx = *count;
    
    strcpy(rec[idx].name, "Player");
    rec[idx].ms = ms;
    sprintf(rec[idx].date, "%04d-%02d-%02d",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    sprintf(rec[idx].time_str, "%02d:%02d:%02d",
            t->tm_hour, t->tm_min, t->tm_sec);
            
    FILE *fp = fopen(SCORE_FILE, "a");
    if (fp == NULL)
    {
        printf("Failed to open file for writing.\n");
        return -1;
    }
    
    fprintf(fp, "%s %d %s %s\n",
            rec[idx].name, rec[idx].ms, rec[idx].date, rec[idx].time_str);
    fclose(fp);
    
    (*count)++;
    return 1;
}