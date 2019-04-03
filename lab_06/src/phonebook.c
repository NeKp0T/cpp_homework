#include <expat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "phonebook.h"
#include "names.h"
#define BUFFER_SIZE 100000

typedef struct {
    phonebook_t *book_reading;
    human_t *human_reading;
    size_t human_phone_cnt;
    char in_phone;
} XML_ParseData_load;


void start_element_load(void *data, const char *element, const char **attribute) {
    XML_ParseData_load *d = data;
    if (strcmp(element, "human") == 0) {
        char *nmf = malloc((strlen(attribute[1]) + 1) * sizeof(char));
        strcpy(nmf, attribute[1]);
        d->human_reading = malloc(sizeof(human_t));
        human_init(d->human_reading);
        d->human_phone_cnt = 0;
        strcpy(d->human_reading->name, strtok(nmf, " "));
        strcpy(d->human_reading->middle_name, strtok(NULL, " "));
        strcpy(d->human_reading->family_name, strtok(NULL, " "));
        free(nmf);
    }
    if (strcmp(element, "phone") == 0)
        d->in_phone = 1;
}

void end_element_load(void *data, const char *element) {
    XML_ParseData_load *d = data;
    if (strcmp(element, "human") == 0)
    {
        push_back_human(d->book_reading, d->human_reading);
        free(d->human_reading);
        d->human_reading = NULL;
    }
    if (strcmp(element, "phone") == 0)
        d->in_phone = 0;
}

void handle_data_load(void *data, const char *content, int length) {
    XML_ParseData_load *d = data;
    if (d->in_phone)
        strncpy(d->human_reading->phones[d->human_phone_cnt++], content, length);
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {
    XML_ParseData_load d;
    d.book_reading = book;
    d.human_phone_cnt = 0;
    d.human_reading = NULL;
    d.in_phone = 0;

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    char *buff = malloc(BUFFER_SIZE * sizeof(char));

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, &d);
    XML_SetElementHandler(parser, start_element_load, end_element_load);
    XML_SetCharacterDataHandler(parser, handle_data_load);

    memset(buff, 0, BUFFER_SIZE);

    size_t len = 0;
    int done = 0;
    do
    {
        len = fread(buff, sizeof(char), BUFFER_SIZE, fp);
        done = len < BUFFER_SIZE;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR)
        {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));

            XML_ParserFree(parser);
            fclose(fp);
            free(buff);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    free(buff);
    qsort(book->humans, book->size, sizeof(human_t), human_compare);


    return 0;
}

const unsigned int indent_size = 4;
int save_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    char *indent = malloc((indent_size + 1) * sizeof(char));
    memset(indent, ' ', indent_size);
    indent[indent_size] = '\0';

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<phonebook>\n");
    for (size_t i = 0; i < book->size; i++) {
        human_t *h = book->humans + i; 
        fprintf(fp, "%s<human name=\"%s %s %s\">\n", indent, h->name, h->middle_name, h->family_name);
        for (size_t j = 0; j < 10 && *h->phones[j]; j++) {
            fprintf(fp, "%s%s<phone>%s</phone>\n", indent, indent, h->phones[j]);
        }
        fprintf(fp, "%s</human>\n", indent);
    }

    fprintf(fp, "</phonebook>\n");
    free(indent);
    fclose(fp);
    return 0;
}

void print_phonebook(phonebook_t *book) {
    printf("%d\n", (int)book->size);
    for (size_t i = 0; i < book->size; i++) {
        human_t h = book->humans[i];
        printf("name: %s\n", h.name);
        printf("middle name: %s\n", h.middle_name);
        printf("family name: %s\n", h.family_name);
        for (size_t j = 0; j < 10 && *h.phones[j] != '\0'; j++)
            printf("phone: %s\n", h.phones[j]);
        printf("\n");
    }
    printf("\n");
}

int human_compare(const void* a, const void* b) {
    return strcmp(((human_t *)a)->family_name, ((human_t *)b)->family_name);
}

void gen_phonebook(phonebook_t *book, size_t size) {
    book->humans = malloc(sizeof(human_t) * size);
    book->size = book->capacity = size;
    for (size_t i = 0; i < size; i++) {
        human_init(&book->humans[i]);
        strcpy(book->humans[i].name, kNames[rand() % NAMES_CNT]);
        strcpy(book->humans[i].middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        strcpy(book->humans[i].family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
        size_t phone_cnt = rand() % 10;
        for (size_t j = 0; j < phone_cnt; j++)
            sprintf(book->humans[i].phones[j], "%d", rand());
    }
    qsort(book->humans, size, sizeof(human_t), human_compare);
}

void clear_phonebook(phonebook_t *book) {
    free(book->humans);
    book->size = book->capacity = 0;
}

human_t get_human(phonebook_t *book, char *family_name) {
    human_t h;
    human_t *pos = bsearch(&h, book->humans, book->size, sizeof(human_t), human_compare);
    assert(strcmp(pos->family_name, family_name) == 0);
    return *pos;
}

void push_back_human(phonebook_t *book, human_t *human) {
    if (book->size == book->capacity) {
        book->capacity = book->capacity * 2 + 1;
        book->humans = realloc(book->humans, book->capacity * sizeof(human_t));
    }
    book->humans[book->size++] = *human;
}

void human_init(human_t *h) {
    memset(h->name, '\0', 256);
    memset(h->middle_name, '\0', 256);
    memset(h->family_name, '\0', 256);
    for (size_t i = 0; i < 10; i++)
        memset(h->phones[i], '\0', 21);
    //*h->phones[i] = '\0';
}

void phonebook_init(phonebook_t *b) {
    b->capacity = 1;
    b->size = 0;
    b->humans = malloc(sizeof(human_t));
}