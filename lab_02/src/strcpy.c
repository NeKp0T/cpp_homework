#include "strcpy.h"

char * strcpy(char * destignation, char * source) {
    char *i = destignation;
    while (*source) {
        *i = *source;
        i++, source++;
    }
    *i = *source;
    return destignation;
}