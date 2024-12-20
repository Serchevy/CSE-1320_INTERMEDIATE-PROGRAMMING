#ifndef IRIS_H
#define IRIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 64
#define MAX_SAMPLES 150
#define NUM_FEATURES 5
#define MAX_STR 16

typedef struct {
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char name[MAX_STR];
} iris_t;

void trim(char *str);
iris_t parse_line(char *csv_line);

#endif
