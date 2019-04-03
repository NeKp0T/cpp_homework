#include <stdio.h>
#include <string.h>
#include "ms_cli.h"
#include "mergesort.h"

int int_compare(const void* a, const void* b) {
    if (*(int *)a < *(int *)b)
        return -1;
    if (*(int *)a > *(int *)b)
        return 1;
    return 0;
}

int char_compare(const void* a, const void* b) {
    if (*(char *)a < *(char *)b)
        return -1;
    if (*(char *)a > *(char *)b)
        return 1;
    return 0;
}

int str_compare(const void* a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char **argv) {
    int n = argc - 2;
    if (strcmp(argv[1], "int") == 0) {
        int *a = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            a[i] = atoi(argv[2 + i]);

        mergesort(a, n, sizeof(int), int_compare);

        for (int i = 0; i < n; i++)
            printf("%d ", a[i]);

        free(a);
    } else if (strcmp(argv[1], "char") == 0) {
        char *a = (char *)malloc(n * sizeof(char));
        for (int i = 0; i < n; i++)
            a[i] = *argv[2 + i];

        mergesort(a, n, sizeof(char), char_compare);

        for (int i = 0; i < n; i++)
            printf("%c ", a[i]);

        free(a);
    } else if (strcmp(argv[1], "str") == 0) {
        char **a = (char **)malloc(n * sizeof(char*));
        cpymem(a, argv + 2, n * sizeof(char*));
        mergesort(a, n, sizeof(char *), str_compare);

        for (int i = 0; i < n; i++)
            printf("%s ", a[i]);

        free(a);
    }

    printf("\n");
}