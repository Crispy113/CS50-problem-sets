#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;

    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int nb_outputs = -1;
    int first_block = -1;

    // Allocate memory to store filename and test for succesful allocation
    char *filename = malloc(8);
    if (filename == NULL)
    {
        printf("Memory allocation error. Program aborted.");
        return 1;
    }

    // Only accept one command line argument, else return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open forensic image. Check if image can be opened. If not, return 1

    // Open input file
    FILE *raw_file = fopen(argv[optind], "r");

    if (raw_file == NULL)
    {
        printf("Error: Cannot open file.");
        return 1;
    }

    // Create pointer for output file
    FILE *img = NULL;

    // Look for beginning of JPEG
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {

        // Check if block is header file. If so, create new file and update filename

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous file
            if (nb_outputs != -1)
            {
                fclose(img);
            }

            // Create new JPEG file, numbering each file starting at 000.jpg
            nb_outputs++;
            first_block = 1;
            sprintf(filename, "%03i.jpg", nb_outputs);

            img = fopen(filename, "w");
        }

        // Write buffer to new file
        if (nb_outputs != -1)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    fclose(raw_file);
    fclose(img);
    free(filename);
}
