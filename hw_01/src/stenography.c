#include "stenography.h"

const char *const extraSimbols = " .,!?\n";

key_t* messageReadKey(FILE *f, size_t *returnReadNum) {
    static const char * const order = "RGB";

    size_t n = 0;
    long int fpos = ftell(f);
    int trash;
    char trashChar;
    while (fscanf(f, "%d %d %c\n", &trash, &trash, &trashChar) == 3)
        n++;
    fseek(f, fpos, SEEK_SET);

    key_t *k = malloc(n * sizeof(key_t));
    if (k == NULL)
        return NULL;
    char component;
    for (size_t i = 0; i < n; i++) {
        fscanf(f, "%d %d %c\n", &k[i].x, &k[i].y, &component);
        k[i].byte = strchr(order, component) - order;
    }

    if (returnReadNum != NULL)
        *returnReadNum = n;

    return k;
}

int8_t messageCharToInt(char c) {
    if ('a' <= c && c <= 'z')
        return c - 'a';
    return strchr(extraSimbols, c) - extraSimbols + 'z' - 'a' + 1;
}

char messageIntToChar(int8_t n) {
    if (n <= 'z' - 'a')
        return 'a' + n;
    return extraSimbols[n - ('z' - 'a') - 1];
}

void messageInsertBit(bmpData *d, char bit, const key_t key) {
    char *byte = (getPixel(d, key.x, key.y) + key.byte);
    if (*byte & (char)1)
        *byte ^= (char)1;
    // *byte &= (~1);
    *byte |= bit;
}

char messageExtractBit(bmpData *d, const key_t key) {
    return (*(getPixel(d, key.x, key.y) + key.byte)) & (char)1;
}

void messageInsert(bmpData *d, key_t *keys, char *msg) {
    for (size_t i = 0; msg[i]; i++) {
        int code = messageCharToInt(msg[i]);
        for (int j = 0; j < 5; j++, code >>= 1) {
            messageInsertBit(d, code & 1, keys[i * 5 + j]);
        }
    }
}

char* messageExtract(bmpData *d, key_t *keys, size_t n) {
    char *msg = malloc((n + 1) * sizeof(char));
    if (msg == NULL)
        return NULL;
    for (size_t i = 0; i < n; i++) {
        char decode = 0;
        for (int j = 0; j < 5; j++) {
            decode >>= 1;
            decode |= messageExtractBit(d, keys[i * 5 + j]) << 4;
        }
        msg[i] = messageIntToChar(decode);
    }
    msg[n] = '\0';
    return msg;
}