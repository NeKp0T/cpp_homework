#pragma once
#include "bmp.h"
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    int32_t x;
    int32_t y;
    int byte;
} key_t;

int8_t messageCharToInt(char c);
int messageColorOrder(char component);

void messageInsertBit(bmpData *d, char bit, const key_t key);
char messageExtractBit(bmpData *d, const key_t key);

void messageInsert(bmpData *d, key_t *keys, char *msg);
char *messageExtract(bmpData *d, key_t *keys, size_t n);

key_t *messageReadKey(FILE *f, size_t *returnReadNum);