#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf ("More arguments are required.\n");
        return -1;
    }
    const int a = argv[1][0] - '0';
    const int b = argv[2][0] - '0';
    if (a * b > 7) {
        printf ("a * b > 7\n");
    } else if (a / b == 2) {
        printf ("a / b == 2\n");
    } else {
        printf ("A third case\n");
    }
    return 0;
}

