// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Create header buffer
    void *buffer8 = malloc(HEADER_SIZE);

    // Copy header from input file to output file
    if (fread(buffer8, 44, 1, input) == 0)
    {
        printf("Error reading input file\n");
        return 1;
    }

    if (fwrite(buffer8, 44, 1, output) == 0)
    {
        printf("Error writing to output file\n");
        return 1;
    }

    free(buffer8);

    int16_t *buffer16 = malloc(2);

    // Copy 16-bit integer into buffer, multiply with factor and write into output

    while (fread(buffer16, 2, 1, input) != 0)
    {
        *buffer16 = *buffer16 * factor;
        fwrite(buffer16, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
