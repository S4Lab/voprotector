#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf ("One argument is required.\n");
        return -1;
    }
    char a;
    a = argv[1][0];
    const char b = argv[1][1];
    if (a != 'a') {
        printf ("first character is wrong!\n");
        return -2;
    } else if (b != 'b') {
        printf ("second character is wrong!\n");
        return -3;
    } else {
        printf ("first and second characters are correct!\n");
    }
    return 0;
}

