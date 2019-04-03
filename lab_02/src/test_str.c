#include "stdio.h"
#include "test_str.h"
#include "strcpy.h"
#include "strcat.h"
#include "strlen.h"
#include "strcmp.h"

#define bool char
#define true 1
#define false 0

void test_strcpy() {
    printf("STRCPY TEST\n");
    char dest[10];
    char strings[4][10] = {
        "Testing",
        "",
        "qweqweqweq",
        {'w', 'e', 'r', 't', 'y', -1, 1, 0}
    };

    for (int i = 0; i < 4; i++) {
        printf("Sorce:\n");
        printf("%s", strings[i]);
        printf("\n");
        printf("Result:\n");
        printf("%s", strcpy(dest, strings[i]));
        printf("\n");
    }
}

void test_strlen() {
    printf("STRLEN TEST\n");
    char strings[4][11] = {
        "Testing",
        "",
        "1234567890",
        {'w', 'e', 'r', 't', 'y', -1, 1, 0}};
    int answers[4] = { 7, 0, 10, 7 };

    for (int i = 0; i < 4; i++)
    {
        printf("Sorce:\n");
        printf("%s", strings[i]);
        printf("\n");
        printf("Result:\n");
        int ans = strlen(strings[i]);
        printf("%d\n", ans);
        if (ans == answers[i])
            printf("Correct!");
        else
            printf("Incorrect! Right answer is %d\n", answers[i]);
        printf("\n");
    }
}
void test_strcat(){
    printf("STRCAT TEST\n");
    char dest[4][40] = {
        "",
        "",
        "BOB!",
        "An app"};
    char strings[4][40] = {
        "",
        "(||||:)",
        "",
        "le a day keeps the doctor away"
    };
    char answers[4][40] = {
        "",
        "(||||:)",
        "BOB!",
        "An apple a day keeps the doctor away"
    };
    for (int i = 0; i < 4; i++)
    {
        printf("Sorce:\n");
        printf("%s\n", dest[i]);
        printf("%s\n", strings[i]);
        printf("Result:\n");
        printf("%s", strcat(dest[i], strings[i]));
        printf("\n");
        printf("Right result:\n");
        printf("%s", answers[i]);
        printf("\n");
    }
}

void test_strcmp() {
    printf("STRCMP TEST\n");
    char str1[8][20] = {
        "",
        "",
        "!",
        "bobbob",
        "bobbobbob",
        "bobbob",
        "bobbobboa",
        "1234567890"};
    char str2[8][20] = {
        "",
        "!",
        "",
        "bobbor",
        "bobbobbzb",
        "bobbo",
        "bobbobbobb",
        "1234567890"
    };
    int answers[8] = {
        0,
        -1,
        1,
        -1,
        -1,
        1,
        -1,
        0
    };
    for (int i = 0; i < 8; i++)
    {
        printf("Strings:\n");
        printf("%s", str1[i]);
        printf("\n");
        printf("%s", str2[i]);
        printf("\n");
        printf("Result:\n");
        bool ans = strcmp(str1[i], str2[i]);
        if ((((ans < 0) == (answers[i] < 0))) && ((ans > 0) == (answers[i] > 0)))
            printf("Correct!");
        else
            printf("Incorrect! Right answer is %d", answers[i]);
        printf("\n");
    }
}