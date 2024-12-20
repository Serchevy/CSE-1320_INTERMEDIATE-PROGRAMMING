#ifndef WORDLE_H
#define WORDLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 16
#define MAX_TRIES 6

typedef struct {
    char **words;
    int num_words;
} wordlist_t;

wordlist_t load_words(char *str);
void trim(char *str1);
char* select_random_answer(wordlist_t random);

#endif
