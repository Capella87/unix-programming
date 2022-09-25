#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define STR_COUNT 5

int main(int argc, char** argv)
{
    char str[101] = "";
    int offsets[STR_COUNT + 1] = { 0, };
    FILE* datafile;
    int num;

    // Create a file named testdata and open the file
    if ((datafile = fopen("testdata", "w+")) == NULL)
    {
        perror("testdata");
        exit(1);
    }

    // Get inputs and write it to the file.
    for (int i = 0; i < STR_COUNT; i++)
    {
        scanf("%[^\n]", str);
        getchar();
        // fwrite(buffer, size of each object, the number of object, FILE*);
        int size = (int)strlen(str);
        fwrite(str, sizeof(char), size, datafile);
        offsets[i + 1] = offsets[i] + size;
    }
    fclose(datafile);

    // Open generated file in read-only mode
    if ((datafile = fopen("testdata", "r")) == NULL)
    {
        perror("testdata");
        exit(1);
    }

    while (1)
    {
        scanf("%d", &num);
        getchar();
        if (num == -1) break;

        // Move the 'cursor' to offsets[num - 1] from the beginning of the file
        fseek(datafile, offsets[num - 1], SEEK_SET);
        fread(str, sizeof(char),  offsets[num] - offsets[num - 1], datafile);
        str[offsets[num] - offsets[num - 1]] = '\0';
        printf("%s\n", str);
    }

    fclose(datafile);
    return 0;
}