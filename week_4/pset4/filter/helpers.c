#include "helpers.h"
#include <math.h>
#include <stdint.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = round((red + green + blue) / 3);
            image[i][j].rgbtGreen = round((red + green + blue) / 3);
            image[i][j].rgbtBlue = round((red + green + blue) / 3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            int sep_red = round(red * .393 + green * .769 + blue * .189);
            int sep_green = round(red * .349 + green * .686 + blue * .168);
            int sep_blue = round(red * .272 + green * .534 + blue * .131);
            
            //Red sep limit check and assign
            if (sep_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sep_red;
            }
            
            //Green sep limit check and assign
            if (sep_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sep_green;
            }
            
            //Blue sep limit check and assign
            if (sep_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sep_blue;
            }
        }
    }
    return;
}


// Reflect image horizontally 
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int auxred[width];
        int auxgreen[width];
        int auxblue[width];
        
        for (int j = 0; j < width; j++)
        {
            auxred[j] = image[i][width - 1 - j].rgbtRed;
            auxgreen[j] = image[i][width - 1 - j].rgbtGreen;
            auxblue[j] = image[i][width - 1 - j].rgbtBlue;
        }
        
        for (int h = 0; h < width; h++)
        {
            image[i][h].rgbtRed = auxred[h];
            image[i][h].rgbtGreen = auxgreen[h];
            image[i][h].rgbtBlue = auxblue[h];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create area to store new average values
    typedef struct
    {
        int avRed;
        int avGreen;
        int avBlue;
    }
    average;
    
    average averages[height][width];
    
    //iterate through pixels
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++) 
        {
            
            //variables to store amount of valid pixels and total color values
            float validpix = 0;
            float totalred = 0;
            float totalgreen = 0;
            float totalblue = 0;
        
            //3x3 box scan for valid pixels
            for (int i = x - 1; i < x + 2; i++)
            {
                for (int j = y - 1; j < y + 2; j++)
                {
                    //check if pixel exists
                    if (i >= 0 && j >= 0 && i < height && j < width)
                    {
                        //if pixel exists store value of each color & store amount of existing pixels
                        totalred += image[i][j].rgbtRed;
                        totalgreen += image[i][j].rgbtGreen;
                        totalblue += image[i][j].rgbtBlue;
                    
                        validpix++;
                    }
                }
            }
            
            //calculate and store average of scanned box using pixel values and amount of valid pixels
            averages[x][y].avRed = round(totalred / validpix);
            averages[x][y].avGreen = round(totalgreen / validpix);
            averages[x][y].avBlue = round(totalblue / validpix);
        }
    }
    
    //assign stored averages to original image
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = averages[a][b].avRed;
            image[a][b].rgbtGreen = averages[a][b].avGreen;
            image[a][b].rgbtBlue = averages[a][b].avBlue;
        }
    }
    return;
}