#include "stenography.h"
#include "bmp.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Lack of arguments\n");
        return 1;
    }
    if (strcmp(argv[1], "crop-rotate") == 0) {
        if (argc != 8) {
            printf("Wrong arguments count\n");
            return 3;
        }

        FILE *fin = fopen(argv[2], "rb");

        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int w = atoi(argv[6]);
        int h = atoi(argv[7]);

        bmpData *original = bmpLoad(fin);
        fclose(fin);
        if (original == NULL) {
            printf("Load error\n");
            return 4;
        }
        bmpData *cropped = crop(original, x, y, w, h);
        if (cropped == NULL) {
            printf("Crop error\n");
            return 5;
        }

        bmpData *rotated = rotate(cropped);
        if (rotated == NULL) {
            printf("Rotate error\n");
            return 6;
        }

        FILE *fout = fopen(argv[3], "wb");
        if (bmpSave(fout, rotated) != 0) {
            printf("Save error\n");
            return 7;
        }
        fclose(fout);

        freeBmp(original);
        freeBmp(cropped);
        freeBmp(rotated);
    } else if (strcmp(argv[1], "insert") == 0) {
        FILE *bmpFileIn = fopen(argv[2], "rb");
        FILE *bmpFileOut = fopen(argv[3], "wb");
        FILE *keyFile = fopen(argv[4], "r");
        FILE *msgFile = fopen(argv[5], "r");

        if (!bmpFileIn || !bmpFileOut || !keyFile || !msgFile) {
            printf("File error\n");
            return 4;
        }

        size_t msgSize;
        key_t *keys = messageReadKey(keyFile, &msgSize);
        if (keys == NULL) {
            printf("Key reading error\n");
            return 8;
        }
        msgSize /= 5;
        fclose(keyFile);

        char *msg = malloc((msgSize + 1) * sizeof(char));
        if (msg == NULL) {
            printf("Memory for message allocating error\n");
            return 9;
        }
        if (fread(msg, msgSize, 1, msgFile) != 1) {
            printf("Message reading error\n");
            return 10;
        }
        fclose(msgFile);
        msg[msgSize] = '\0';

        bmpData *picture = bmpLoad(bmpFileIn);
        if (picture == NULL) {
            printf("BMP load error\n");
            return 4;
        }
        fclose(bmpFileIn);

        messageInsert(picture, keys, msg);

        if (bmpSave(bmpFileOut, picture) != 0) {
            printf("BMP save error\n");
            return 7;
        }
        fclose(bmpFileOut);

        freeBmp(picture);
        free(keys);
        free(msg);
    }
    else if (strcmp(argv[1], "extract") == 0) {
        FILE *bmpFileIn = fopen(argv[2], "rb");
        FILE *keyFile = fopen(argv[3], "r");
        FILE *msgFile = fopen(argv[4], "w");

        if (!bmpFileIn || !keyFile || !msgFile) {
            printf("File error\n");
            return 4;
        }

        size_t msgSize;
        key_t *keys = messageReadKey(keyFile, &msgSize);
        if (keys == NULL) {
            printf("Key reading error\n");
            return 8;
        }
        fclose(keyFile);

        bmpData *picture = bmpLoad(bmpFileIn);
        if (picture == NULL) {
            printf("Load error\n");
            return 4;
        }
        fclose(bmpFileIn);

        char *msg = messageExtract(picture, keys, msgSize / 5);
        if (msg == NULL) {
            printf("Message extraction error\n");
            return 11;
        }
        if (fprintf(msgFile, "%s", msg) < 0)
        {
            printf("Message saving error\n");
            return 12;
        }
        fclose(msgFile);

        freeBmp(picture);
        free(keys);
        free(msg);
    }
    else
    {
        printf("Unknown argument\n");
        return 2;
    }

    return 0;
}
