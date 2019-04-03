#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stddef.h>


#pragma pack(push, 1)

typedef struct {
    char BM[2];
    int32_t FileSize;
    int16_t Reserved1;
    int16_t Reserved2;
    int32_t Offset;
} bmpFileHeader;

typedef struct {
    int32_t Size;
    int32_t Width;
    int32_t Height;
    int16_t Planes;
    int16_t BitCount;
    int32_t Compression;
    int32_t SizeImage;
    int32_t ResolutionX;
    int32_t ResolutionY;
    int32_t ColorsUsed;
    int32_t ColorsUseful;
} bmpInfoHeader;


#pragma pack(pop)

typedef struct {
    int32_t w, h;
    int32_t paddedW;
    char *image;
    int32_t ResolutionX, ResolutionY;
    int16_t byteCount;
} bmpData;

bmpData* bmpDataImitate(int32_t w, int32_t h, bmpData *f);
bmpData* bmpDataInit(int32_t w, int32_t h, int16_t byteCount, int32_t ResolutionX, int32_t ResolutionY);

bmpData* bmpLoad(FILE *fin);
int bmpSave(FILE *fout, bmpData *d);

char* getPixel(bmpData *f, int i, int j);
bmpData* crop(bmpData *f, int x, int y, int w, int h);
bmpData* rotate(bmpData *f);

void printInfo(bmpInfoHeader h);

void freeBmp(bmpData *f);