#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./recover 'your_inputfile'\n");
        return 1;
    }
    // check to open and read input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // counter for the restored images
    int count_images = 0;
    // a file pointer to use for the output data which come from input file
    FILE *output_file = NULL;

    // create the buffer array for 512 bytes
    BYTE buffer[512];

    // string to hold the jpg filename
    char jpgfilename[8] = {0};

    // read 512 bytes, aka one block, from inptr and store it in the buffer
    while (fread(buffer, sizeof(BYTE) * 512, 1, inptr) == 1)
    {
        // check the first four bytes of each block for the jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close output_file if jpeg was found before and written
            if (output_file != NULL)
            {
                fclose(output_file);
            }
            // write jpeg into filename
            sprintf(jpgfilename, "%03i.jpg", count_images++);
            // open new jpgfilename for writing
            output_file = fopen(jpgfilename, "w");
        }

        // write each block to the new file and check if output_file is already open
        // keep writing to jpg file if no new jpg is found
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, output_file);
        }
    }

    // close last opened output_file
    if (output_file != NULL)
    {
        fclose(output_file);
    }
    // close inputfile
    fclose(inptr);

    return 0;
}
