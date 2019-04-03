#include <expat.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "phonebook.h"


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Invalid arguments\n");
        return 1;
    }
    srand(time(NULL));
    phonebook_t b;
    phonebook_init(&b);
    int result;
    result = load_phonebook_xml(argv[1], &b);
    if (result != 0) {
        printf("Load error\n");
        return 2;
    }

    print_phonebook(&b);

    clear_phonebook(&b);
    gen_phonebook(&b, rand() % 8);
    
    result = save_phonebook_xml("fout.txt", &b);
    if (result != 0) {
        printf("Saving error\n");
        return 3;
    }

    clear_phonebook(&b);

    return 0;
}
