#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void get_random_word(int min, int max, char *filename, char *answer) {
    int target_line = arc4random_uniform(max - min + 1) + min;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char buffer[7]; // 5 letters + newline + null terminator
    int current_line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (current_line == target_line) {
            buffer[strcspn(buffer, "\r\n")] = 0;
            strcpy(answer, buffer);
            break;
        }
        current_line++;
    }
    fclose(file);
}
void input_word(char *guess) {
    printf("guess: ");
    if (fgets(guess, sizeof(guess), stdin) != NULL) {
    guess[strcspn(guess, "\n")] = 0;
    }   
}
void compare_words (char *answer, char *guess, int *result) {
    int compare = strncasecmp(answer, guess, 5);
    *result = compare;
}
void feedback(char *answer, char *guess) {
    int result[5] = {0};
    int answer_used[5] = {0};
    int guess_used[5] = {0};
    for (int i = 0; i < 5; i++) {
        if (tolower(guess[i]) == tolower(answer[i])) {
            result[i] = 1;
            answer_used[i] = 1;
            guess_used[i] = 1;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (guess_used[i]) continue;
        for (int j = 0; j < 5; j++) {
            if (answer_used[j]) continue;
            if (tolower(guess[i]) == tolower(answer[j])) {
                result[i] = 2;
                answer_used[j] = 1;
                break;
            }
        }
    }
    printf("|");
    for (int i = 0; i < 5; i++) {
        if (result[i] == 1)      printf("✓|");
        else if (result[i] == 2) printf("○|");
        else                     printf("✗|");
    }
    printf("\n");
}
int main() {
   #ifndef WORDS_PATH
    #define WORDS_PATH "words.txt"
    #endif
    char answer[6];
    get_random_word(1, 21953, WORDS_PATH, answer);
    printf("Welcome to Wordle! Try to guess the 5-letter word.\n");
    char guess[7];
    int result = 1;
    input_word(guess);
    compare_words(answer, guess, &result);
    feedback(answer, guess);
        while (result != 0) {
        input_word(guess);
        compare_words(answer, guess, &result);

        feedback(answer, guess);
    }
    printf("\n");
    printf("Congratulations! You've guessed the word: %s\n", answer);
    return 0;
}