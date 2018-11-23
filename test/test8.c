#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
    const int magic = strcmp (argv[1], "magicvalue") == 0;
    if (!magic) {
        printf ("magic value is missing\n");
    } else {
        printf ("magicvalue is given\n");
    }
    return 0;
}

