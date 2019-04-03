#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "bmp.h"

int paddedSize(int l) {
    if (l == 0)
        return 0;
    return (l - 1) / 4 * 4 + 4;
}

bmpData* bmpDataInit(int32_t w, int32_t h, int16_t byteCount, int32_t ResolutionX, int32_t ResolutionY) {
    bmpData *d = malloc(sizeof(bmpData));
    if (d == NULL)
        return NULL;
    d->w = w;
    d->h = h;
    d->paddedW = paddedSize(w * byteCount);
    d->byteCount = byteCount;
    d->ResolutionX = ResolutionX;
    d->ResolutionY = ResolutionY;
    d->image = malloc(d->h * d->paddedW * d->byteCount);
    if (d->image == NULL) {
        free(d);
        return NULL;
    }
    memset(d->image, 0, d->h * d->paddedW * d->byteCount);
    return d;
}

bmpData* bmpDataImitate(int32_t w, int32_t h, bmpData *f) {
    return bmpDataInit(w, h, f->byteCount, f->ResolutionX, f->ResolutionY);
}

bmpData* bmpLoad(FILE *fin) {
    if (fin == NULL)
        return NULL;
    bmpFileHeader fhead;
    bmpInfoHeader head;
    fread(&fhead, sizeof(bmpFileHeader), 1, fin);
    fread(&head, sizeof(bmpInfoHeader), 1, fin);
    
    bmpData *d = bmpDataInit(head.Width, head.Height, head.BitCount / 8, head.ResolutionX, head.ResolutionY);
    if (d == NULL)
        return NULL;
    
    fseek(fin, fhead.Offset, SEEK_SET);
    fread(d->image, d->paddedW * d->h, 1, fin);

    return d;
}

int bmpSave(FILE *fout, bmpData *d) {
    if (fout == NULL)
        return 1;

    bmpFileHeader fhead;
    bmpInfoHeader head;
    fhead.BM[0] = 'B';
    fhead.BM[1] = 'M';
    fhead.FileSize = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader) + d->paddedW * d->h;
    fhead.Reserved1 = 0;
    fhead.Reserved2 = 0;
    fhead.Offset = sizeof(bmpInfoHeader) + sizeof(bmpFileHeader);
    head.Size = sizeof(bmpInfoHeader);
    head.Width = d->w;
    head.Height = d->h;
    head.Planes = 1;
    head.BitCount = 8 * d->byteCount;
    head.Compression = 0;
    head.SizeImage = d->paddedW * d->h;
    head.ResolutionX = d->ResolutionX;
    head.ResolutionY = d->ResolutionY;
    head.ColorsUsed = 0;
    head.ColorsUseful = 0;

    fwrite(&fhead, sizeof(bmpFileHeader), 1, fout);
    fwrite(&head, sizeof(bmpInfoHeader), 1, fout);
    fwrite(d->image, head.SizeImage, 1, fout);
  
    return 0;
}

char *getPixel(bmpData *f, int i, int j) {
    return f->image + f->paddedW * (f->h - j - 1) + i * f->byteCount;
}

bmpData *crop(bmpData *f, int x, int y, int w, int h) {
    if (x < 0 || y < 0 || x + w > f->w  || y + h > f->h)
        return NULL;
    bmpData *res = bmpDataImitate(w, h, f);
    if (res == NULL)
        return NULL;

    for (int i = 0; i < h; i++)
        memcpy(getPixel(res, 0, i), getPixel(f, x, i + y), w * f->byteCount);

    return res;
}

void freeBmp(bmpData *d) {
    free(d->image);
    free(d);
}

bmpData *rotate(bmpData *f) {
    bmpData *res = bmpDataImitate(f->h, f->w, f);
    if (res == NULL)
        return NULL;
 
    for (int i = 0; i < res->w; i++)
        for (int j = 0; j < res->h; j++)
            memcpy(getPixel(res, res->w - 1 - i, j), getPixel(f, j, i), res->byteCount);

    return res;
}

void printInfo(bmpInfoHeader h) {
    printf("Size: %d\n",        h.Size);
    printf("Width: %d\n",       h.Width);
    printf("Height: %d\n",      h.Height);
    printf("Planes: %d\n",      h.Planes);
    printf("BitCount: %d\n",    h.BitCount);
    printf("Compression: %d\n", h.Compression);
    printf("SizeImage: %d\n",   h.SizeImage);
    printf("ResolutionX: %d\n", h.ResolutionX);
    printf("ResolutionY: %d\n", h.ResolutionY);
    printf("ColorsUsed: %d\n",  h.ColorsUsed);
    printf("ColorsUseful: %d\n",h.ColorsUseful);
}
