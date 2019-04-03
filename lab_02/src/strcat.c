#include "strcat.h"

char * strcat(char * destination, const char * source) {
    char *i = destination;
    while (*i)
        i++;
    while (*source)
    {
        *i = *source;
        i++, source++;
    }
    *i = *source;
    return destination;
}