#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf ("More arguments are required.\n");
        return -1;
    }
    if (argv != 0) {
        printf ("argv is not null!\n");
    } else {
        printf ("argv is null!!!\n");
        return -2;
    }
    return 0;
}

