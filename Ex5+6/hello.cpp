/*
 * File: hello.c
 */
// problem #1 - no inclusion for <stdio.h> while trying to use printf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *string = 0, *string_so_far = 0; // problem #4 - string is not initialized
    int i, length;
    length = 0;
    for (i = 0; i < argc; i++)
    {
        length += strlen(argv[i]) + 1;
        string = /* problem #2 - add casting/*/ (char *)malloc(length + 1);

        /*  * Copy the string built so far. */
        if (string_so_far != (char *)0)
            strcpy(string, string_so_far);
        else
            *string = '\0';
        strcat(string, argv[i]);
        if (i < argc - 1)
            strcat(string, " ");
        free(string_so_far); // problem #5 - needed to free string_so_far
        string_so_far = string;
    }
    printf("You entered: %s\n", string_so_far);
    free(string); // problem #3 - memory leak
    return (0);
}
