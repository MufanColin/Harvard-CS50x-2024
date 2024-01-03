#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[]) {
    if (argc == 2) {
        printf("hello, %s!\n", argv[1]);
    } else {
        printf("Missing command-line arguments!\n");
        return 1;
    }
    return 0;
}

// We can use echo $? to check the exit status of the most recent execution.
