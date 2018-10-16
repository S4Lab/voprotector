#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf ("More arguments are required.\n");
        return -1;
    }
    if (argc == 2) {
        printf ("There are two arguments.\n");
    } else {
        printf ("A lot of arguments!\n");
        return -2;
    }
    return 0;
}

