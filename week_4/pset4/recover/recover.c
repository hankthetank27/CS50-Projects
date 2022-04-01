#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    //check if memory card exists
    if (argv[1] == 0)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //open memory card in read mode
    FILE *card = fopen(argv[1], "r");
    
    //define variables for recover process
    BYTE buffer[512];
    int filenum = 0;
    bool fileexist = false;
    FILE *newimage;
    char *filename = malloc(sizeof(char) * 7);
    
    //read 512 bytes into buffer until end of card
    while (fread(&buffer, sizeof(BYTE), 512, card))
    {
        
        //check if start is jpg by looking at first 4 bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            //close previous jpg and create new jpg
            if (fileexist)
            {
                fclose(newimage);
                sprintf(filename, "%03i.jpg", filenum);
                newimage = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, newimage);
                filenum++;
            }
            
            //create 1st jpg
            else
            {
                sprintf(filename, "%03i.jpg", filenum);
                newimage = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, newimage);
                filenum++;
                fileexist = true;
            }
        }
        
        //continue to write if new header does not exist
        else if (fileexist)
        {
            fwrite(&buffer, sizeof(BYTE), 512, newimage);
        }
    }
    free(filename);
    return 0;
}