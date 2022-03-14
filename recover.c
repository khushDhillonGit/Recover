#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
 
typedef uint8_t header;

int main(int argc, char *argv[])
{
    // Check for correct input
    if (argc != 2)
    {
        printf("Provide correct fine name\n");
        return 1;
    }
    //to open memory card
    FILE *source = fopen(argv[1], "r");
    
    // check for null value
    if (source == NULL)
    {
        printf("File is not opening\n");
        return 1;
    }

   
    header buffer[512];
    // variable for counting
    int count = 0;
    //output file pointer
    FILE *output = NULL;
    //first file name
    char *as = "000.jpg";
    char filename[8];
    //loop for each block checking
    while (fread(&buffer, sizeof(header), 512, source))
    {  
            
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {   
            if (count > 0)
            {
                sprintf(filename, "%03i.jpg", count);
            }
            count++;
            if (count == 1)
            {
                output = fopen(as, "w");

                fwrite(&buffer, sizeof(header), 512, output);
            }
            else
            {
                fclose(output);
                output = fopen(filename, "w");
                fwrite(&buffer, sizeof(header), 512, output);
            }
        }  
        else if (count != 0)
        {
    
            fwrite(&buffer, sizeof(header), 512, output);
            
        }
    }
    
    //closing of files
    fclose(output);
    fclose(source);
    

}