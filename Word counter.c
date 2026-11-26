#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_LEN 1000
#define MAX_WORDS 500
#define MAX_WORD_LEN 50
int main(void) {
    char text[MAX_TEXT_LEN];
    char unique_words[MAX_WORDS][MAX_WORD_LEN];
    int unique_count = 0;
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 0;
    }
    char *p = text;
    while (*p != '\0') {
        if (isalpha(*p)) {
            char current_word[MAX_WORD_LEN];
            int len = 0;
            while (isalpha(*p)) {
                current_word[len++] = tolower(*p);
                p++;
            }
            current_word[len] = '\0';
            int is_exist = 0;
            for (int i = 0; i < unique_count; i++) {
                if (strcmp(unique_words[i], current_word) == 0) {
                    is_exist = 1;
                    break;
                }
            }
            if (!is_exist) {
                strcpy(unique_words[unique_count], current_word);
                unique_count++;
            }
        } else {
            p++;
        }
    }
    printf("%d\n", unique_count);
    return 0;
}

