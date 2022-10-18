#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dict.h"
#include "util.h"
#include "wordle.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s [k] [file] [quantum]\n", argv[0]);
        printf("  k       - word length\n");
        printf("  file    - textfile containing the words one per line\n");
        printf(
            "  quantum - whether quantum wordle should be played (y/n), "
            "default false\n");
        exit(EXIT_FAILURE);
    }

    // initialize randomness using current time
    srand48(time(NULL));
    int k = atoi(argv[1]);
    char *filename = argv[2];
    bool quantum = false;
    if (argc > 3) {
        if (argv[3][0] == 'y' || argv[3][0] == 'Y' || argv[3][0] == '1' ||
            argv[3][0] == 't' || argv[3][0] == 'T') {
            quantum = true;
        }
    }
    // allocate space to store the randomly selected word
    // +1 for null terminator
    char *selected = malloc(k + 1);
    char *selected2 = quantum ? malloc(k + 1) : NULL;
    // read file containing all words
    Trie *set = generateDict(filename, k, selected, selected2);
    printf("The selected word is \"%s\". (Do not tell anyone)\n", selected);
    if (quantum) {
        printf("The selected dual word is \"%s\". (Do not tell anyone)\n",
               selected2);
    }
    int rounds = 0;
    // set boolean to false so you can start the while loop
    bool gameended = false;
    while (gameended == false) {
        char *attempt = guess(set, k);

        feedback_result *feedback =
            getFeedback(attempt, selected, selected2,
                        k);  // take users guess and generate the feedback

        if (checkWin(feedback, k) ==
            false) {  // if the word is incorrect print feedback and increment
                      // round counter
            printFeedback(feedback, k);
            rounds = rounds + 1;
        } else {
            printFeedback(feedback, k);
            rounds = rounds + 1;
            gameended = true;
        }
        free(feedback);
        free(attempt);
    }
    // NOT_IMPLEMENTED;

    printf("You needed %d attempts.\n", rounds);

    // frees all memory of the dictionary
    destroy(set);
    free(selected);
    if (selected2) free(selected2);

    return EXIT_SUCCESS;
}
