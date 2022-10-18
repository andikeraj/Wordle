#include "wordle.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dict.h"
#include "util.h"

Trie *generateDict(char *filename, int k, char *selected1, char *selected2) {
    selected2 = NULL;
    FILE *fileopen = fopen(filename, "r");
    struct Trie *dict = create();
    char *read = calloc(k + 1, sizeof(char));
    read[k] = 0;
    int linecounter = 0;
    while (fscanf(fileopen, "%5s", read) != EOF) {
        insert(dict, read);
        linecounter++;
    }
    fclose(fileopen);

    fileopen = fopen(filename, "r");
    int rndmness = (linecounter + 1) * drand48();
    for (int i = 0; i <= rndmness; i++) {
        fscanf(fileopen, "%5s", selected1);
    }
    free(read);
    fclose(fileopen);
    return dict;
    /*UNUSED(filename);
    UNUSED(k);
    UNUSED(selected1);
    UNUSED(selected2);
    NOT_IMPLEMENTED;*/
}
// function that turns upper case letters to lowercase
char *capstolower(char *guess, int k) {
    for (int i = 0; i < k; i++) {
        if (guess[i] >= 'A' && guess[i] <= 'Z') {
            guess[i] = guess[i] + 32;
        }
    }
    return guess;
}

char *guess(Trie *dict, int k) {
    char *guess = calloc(k + 1, sizeof(char));
    printf("Please input your guess: ");
    scanf("%5s", guess);
    capstolower(guess, k);
    if (dict == NULL) {
        return guess;
    }
    if (lookup(dict, guess) == true) {
        return guess;
    }

    while (lookup(dict, guess) == false) {
        printf("Invalid word. Try again: ");
        scanf("%5s", guess);
        capstolower(guess, k);
    }
    return guess;

    /*UNUSED(dict);
    UNUSED(k);
    NOT_IMPLEMENTED;*/
}

feedback_result *getFeedback(char *guess, char *word1, char *word2, int k) {
    word2 = NULL;
    feedback_result *result = calloc(k + 1, sizeof(feedback_result));
    int *m = calloc(k, sizeof(int));
    int *n = calloc(k, sizeof(int));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (guess[i] == word1[j] && i == j) {
                result[i] = CORRECT;
                if (m[j] != 0) {
                    result[m[j] - 1] = WRONG;
                }
                m[j] = i + 1;
                n[i] = j + 1;
            }
            if (guess[i] == word1[j] && i != j && m[j] == 0 && n[i] == 0) {
                result[i] = WRONGPOS;
                m[j] = i + 1;
                n[i] = i + 1;
            }
            if (guess[i] != word1[i] && result[i] == 0) {
                result[i] = WRONG;
            }
        }
    }

    free(m);
    free(n);
    return result;
    /*UNUSED(guess);
    UNUSED(word1);
    UNUSED(word2);
    UNUSED(k);
    NOT_IMPLEMENTED;*/
}

void printFeedback(feedback_result *feedback, int k) {
    printf("Result: ");
    for (int i = 0; i < k; i++) {
        if (feedback[i] == CORRECT) {
            printf("🟩");
        } else if (feedback[i] == WRONGPOS) {
            printf("🟨");
        } else {
            printf("⬛");
        }
    }
    printf("\n");
    /*UNUSED(feedback);
    UNUSED(k);
    NOT_IMPLEMENTED;*/
}

bool checkWin(feedback_result *feedback, int k) {
    int counter = 0;
    for (int i = 0; i < k; i++) {
        if (feedback[i] == CORRECT) {
            counter++;
        }
    }
    if (counter == k) {
        return true;
    }
    return false;
    /*UNUSED(feedback);
    UNUSED(k);
    NOT_IMPLEMENTED;*/
}
