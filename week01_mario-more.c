#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Load variables
    int height;
    int level;
    level = 0;

    // Get user input "height". Only accept nb. 1-8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Build pyramid.

    // Control height
    for (int i = 0; i < height; i++)
    {

        level = level + 1;

        // Control width

        // Spaces, left
        for (int k = 0; k < (height - level); k++)
        {
            printf(" ");
        }

        // Bricks left
        for (int l = 0; l < level; l++)
        {
            printf("#");
        }

        // Spaces between pyramids
        printf("  ");

        // Bricks right
        for (int l = 0; l < level; l++)
        {
            printf("#");
        }

        // Next line
        printf("\n");
    }

}
