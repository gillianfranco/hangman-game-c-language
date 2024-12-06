#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"
// Globals variables
char attempts[26];
char wordSecret[WORD_SIZE];
int quantityOfAttempts = 0;

int main() {

    choose_secret_word();

    opening();

    do {
        draws_gallows();
        guess();
    } while (!victory() && !hanged());

    printf("Word: %s\n", wordSecret);

    if (victory()){
        printf("\nCongrats! You won!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n");
    }  else {
        printf("\nYou lost. Try again later!\n");
        printf("The word secret is %s.\n", wordSecret);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    add_new_word();

    return 0;
}

void choose_secret_word() {
    FILE* file;

    file = fopen("/workspaces/hangman-game-c-language/words.txt", "r");
    if (file == 0) {
        printf("Sorry. The file was not found.");
        exit(0);
    }
    
    int amountOfWords;
    fscanf(file, "%d", &amountOfWords);

    srand(time(0));
    int randNumber = rand() % amountOfWords;

    for (int i = 0; i <= randNumber; i++) {
        fscanf(file, "%s", wordSecret);
    }

    fclose(file);
}

void opening() {

    printf(" __  __                                                                                          \n");
    printf("/\\ \\/\\ \\                                                                                     \n");
    printf("\\ \\ \\_\\ \\     __      ___      __     ___ ___      __      ___                              \n");
    printf(" \\ \\  _  \\  /'__`\\  /' _ `\\  /'_ `\\ /' __` __`\\  /'__`\\  /' _ `\\                        \n");
    printf("  \\ \\ \\ \\ \\/\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\L\\ \\/\\ \\/\\ \\/\\ \\/\\ \\L\\.\\_/\\ \\/\\ \\ \n");
    printf("   \\ \\_\\ \\_\\ \\__/.\\_\\ \\_\\ \\_\\ \\____ \\ \\_\\ \\_\\ \\_\\ \\__/.\\_\\ \\_\\ \\_\\    \n");
    printf("    \\/_/\\/_/\\/__/\\/_/\\/_/\\/_/\\/___L\\ \\/_/\\/_/\\/_/\\/__/\\/_/\\/_/\\/_/                \n");
    printf("                               /\\____/                                                          \n");
    printf("                               \\_/__/                                                           \n");
    printf(" ____                                                                                            \n");
    printf("/\\  _`\\                                                                                        \n");
    printf("\\ \\ \\L\\_\\     __      ___ ___      __                                                       \n");
    printf(" \\ \\ \\L_L   /'__`\\  /' __` __`\\  /'__`\\                                                    \n");
    printf("  \\ \\ \\/, \\/\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\/\\  __/                                           \n");
    printf("   \\ \\____/\\ \\__/.\\_\\ \\_\\ \\_\\ \\_\\ \\____\\                                           \n");
    printf("    \\/___/  \\/__/\\/_/\\/_/\\/_/\\/_/\\/____/                                                  \n");
    printf("                                                                                                 \n");
    printf("================================================================================================ \n\n");
}

void draws_gallows() {
    int mistakes = wrongAttempts();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %s    \n", (mistakes >= 1 ? "(_)" : "   "));
    printf(" |      %s   \n", (mistakes >= 2 ? "\\|/" : "   "));
    printf(" |       %s     \n", (mistakes >= 3 ? "|" : " "));
    printf(" |      %s   \n", (mistakes >= 4 ? "/ \\" : "   "));
    printf(" |             \n");
    printf("_|___          \n\n");

    printf("Word: ");

    for (int i = 0; i < (int)strlen(wordSecret); i++) {
        
        int letterFound = already_guessed(wordSecret[i]);
        
        if (letterFound) {
            printf("%c ", wordSecret[i]);
        } else {
            printf("_ ");
        }
    }
}

void guess() {
    char guess;

    printf("\n\nEnter a letter: ");
    scanf(" %c", &guess);
    printf("\n");

    attempts[quantityOfAttempts] = guess;
    quantityOfAttempts++;
}

int already_guessed(char letter) {
    int letterFound = 0;

    for (int j = 0; j < quantityOfAttempts; j++){
        if (attempts[j] == letter) {
            letterFound = 1;
            break;
        }
    }

    return letterFound;
}

int wrongAttempts() {
    int wrongAttempts = 0;

    for (int i = 0; i < quantityOfAttempts; i++) {
        int rightAttempts = 0;
        for (int j = 0; j < (int)strlen(wordSecret); j++) {
            if (attempts[i] == wordSecret[j]) {
                rightAttempts++;
                break;
            }
        }

        if (!rightAttempts) wrongAttempts++;
    }

    return wrongAttempts;
}

int victory() {
    for (int i = 0; i < (int)strlen(wordSecret); i++) {
        if(!already_guessed(wordSecret[i])) {
            return 0;
        }
    }

    return 1;
}

int hanged() {
    return wrongAttempts() == 5;
}

void add_new_word() {

    char wantToAdd;

    printf("\nDo you want add a new word in the game? [Y/N] ");
    scanf(" %c", &wantToAdd);

    if (wantToAdd == 'Y' || wantToAdd == 'y') {
        FILE* file;
        file = fopen("/workspaces/hangman-game-c-language/words.txt", "r+");

        char newWord[WORD_SIZE];
        printf("\nEnter the new word: ");
        scanf("%s", newWord);

        int wordsQuantity;
        fscanf(file, "%d", &wordsQuantity);
        wordsQuantity++;

        fseek(file, 0, SEEK_SET);
        fprintf(file, "%d", wordsQuantity);

        fseek(file, 0, SEEK_END);
        fprintf(file, "\n%s", newWord);

        fclose(file);

        printf("Word added successfully!\n");
    } else {
        printf("\nClosing the program...\n");
    }
}