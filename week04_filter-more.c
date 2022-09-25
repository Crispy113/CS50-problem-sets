/* Note: To solve this problem set, we had to coding the filter module of an image filtering program.
* The rest of the program was already written and is therefore not included here. You'll need the rest
* of the program to run this file. Go to https://cs50.harvard.edu/x/2022/psets/4/filter/more/ to download.
*/

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go to each pixel in image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Define temp variables for all 3 colours and copy pixel values into temp
            float tmpR = image[h][w].rgbtRed;
            float tmpG = image[h][w].rgbtGreen;
            float tmpB = image[h][w].rgbtBlue;

            // Calculate average of the three colour channels
            float avr = ((tmpR + tmpG + tmpB) / 3);

            // Write this average into each colour channel of pixel
            image[h][w].rgbtRed = round(avr);
            image[h][w].rgbtGreen = round(avr);
            image[h][w].rgbtBlue = round(avr);
        }
    } // Repeat for each pixel

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Go to each pixels on the left side of image. If width is odd number, don't go to middle pixels.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width / 2); w++)
        {
            // Copy each colour value into temp
            int tmpR = image[h][w].rgbtRed;
            int tmpG = image[h][w].rgbtGreen;
            int tmpB = image[h][w].rgbtBlue;

            // Copy values of opposite pixel (mirrored along y-axis) into original pixel
            image[h][w].rgbtRed = image[h][width - (w + 1)].rgbtRed;
            image[h][w].rgbtGreen = image[h][width - (w + 1)].rgbtGreen;
            image[h][w].rgbtBlue = image[h][width - (w + 1)].rgbtBlue;

            // Copy values of original pixel from temp into opposite pixel
            image[h][width - (w + 1)].rgbtRed = tmpR;
            image[h][width - (w + 1)].rgbtGreen = tmpG;
            image[h][width - (w + 1)].rgbtBlue = tmpB;
        }
    } // Repeat for each pixel

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image
    RGBTRIPLE imagecopy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            imagecopy[h][w].rgbtRed = image[h][w].rgbtRed;
            imagecopy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            imagecopy[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    // Go to each pixel in image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float blurR = 0;
            float blurG = 0;
            float blurB = 0;
            int pxlcount = 0;

            // For each pixel, scan a 3x3 matrix around the image, ignoring edges
            for (int h2 = h - 1; h2 < h + 2; h2++)
            {
                for (int w2 = w - 1; w2 < w + 2; w2++)
                {
                    // If out of bounds, ignore
                    if (h2 < 0 || h2 >= height || w2 < 0 || w2 >= width)
                    {
                    }

                    // Add values to blur-variable, for each colour
                    else
                    {
                        blurR = blurR + imagecopy[h2][w2].rgbtRed;
                        blurG = blurG + imagecopy[h2][w2].rgbtGreen;
                        blurB = blurB + imagecopy[h2][w2].rgbtBlue;

                        // Count how many pixels are visited
                        pxlcount++;
                    }
                }
            }

            // For each colour, calculate average value of visited pixels
            blurR = blurR / pxlcount;
            blurG = blurG / pxlcount;
            blurB = blurB / pxlcount;

            // Write pixel to image
            image[h][w].rgbtRed = round(blurR);
            image[h][w].rgbtGreen = round(blurG);
            image[h][w].rgbtBlue = round(blurB);
        }
    } // Repeat for each pixel

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Create copy of image
    RGBTRIPLE imagecopy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            imagecopy[h][w].rgbtRed = image[h][w].rgbtRed;
            imagecopy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            imagecopy[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

// Store values of Gx and Gy kernels
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


// Process the image

    // Visit each pixel in image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float GxR = 0;
            float GxG = 0;
            float GxB = 0;

            float GyR = 0;
            float GyG = 0;
            float GyB = 0;

            //For each pixel in image, scan a 3x3 matrix around the pixel
            for (int h2 = h - 1, Gh = 0; h2 < h + 2; h2++, Gh++)
            {
                for (int w2 = w - 1, Gw = 0; w2 < w + 2; w2++, Gw++)
                {

                    // Exclude pixel if out of bounds
                    if (h2 < 0 || h2 >= height || w2 < 0 || w2 >= width)
                    {
                    }

                    //Else, calculate Gx and Gy values for each colour
                    else
                    {
                        GxR = GxR + (imagecopy[h2][w2].rgbtRed * Gx[Gh][Gw]);
                        GxG = GxG + (imagecopy[h2][w2].rgbtGreen * Gx[Gh][Gw]);
                        GxB = GxB + (imagecopy[h2][w2].rgbtBlue * Gx[Gh][Gw]);

                        GyR = GyR + (imagecopy[h2][w2].rgbtRed * Gy[Gh][Gw]);
                        GyG = GyG + (imagecopy[h2][w2].rgbtGreen * Gy[Gh][Gw]);
                        GyB = GyB + (imagecopy[h2][w2].rgbtBlue * Gy[Gh][Gw]);
                    }
                }
            }


            // Combine Gx and Gy values for all 3 colours, using below formula

            float GR = sqrt(pow(GxR, 2) + pow(GyR, 2));

            if (GR > 255)
            {
                GR = 255;
            }
            else
            {
                GR = round(GR);
            }

            float GG = sqrt(pow(GxG, 2) + pow(GyG, 2));
            if (GG > 255)
            {
                GG = 255;
            }
            else
            {
                GG = round(GG);
            }

            float GB = sqrt(pow(GxB, 2) + pow(GyB, 2));
            if (GB > 255)
            {
                GB = 255;
            }
            else
            {
                GB = round(GB);
            }

            // Write pixel to image

            image[h][w].rgbtRed = GR;
            image[h][w].rgbtGreen = GG;
            image[h][w].rgbtBlue = GB;
        }
    } // Repeat for each pixel

    return;
}
