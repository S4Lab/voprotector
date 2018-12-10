#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
    const int x = argv[1][0] - '0';
    const int y = argv[1][1] - '0';
    if (x % y == 0) {
        printf ("first digit is divided by the second digit\n");
    } else {
        printf ("first digit is NOT divided by the second digit\n");
    }
    return 0;
}

