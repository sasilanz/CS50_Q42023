#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1 - DONE
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    else if (strcmp(argv[1] + strlen(argv[1]) - 4, ".wav") != 0)
    {
        printf("input file is not a .wav\n");
        return 1;
    }
    else if (strcmp(argv[2] + strlen(argv[2]) - 4, ".wav") != 0)
    {
        printf("output file is not a .wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2 - DONE
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    // TODO #3 - DONE
    // create the Header buffer array
    WAVHEADER header;
    // read header from input file
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4 - DONE
    if (!check_format(header))
    {
        printf("Input is not a WAV file\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5 - DONE
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Output file could not be created.\n");
        return 1;
    }

    // Write header to file
    // TODO #6 - DONE
    fwrite(&header, sizeof(header), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7 - DONE
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8 - DONE
    // create an array to store each block to read in
    BYTE buffer[blockSize];

    // move pointer to the end of file - from fseek documentation
    fseek(input, 0, SEEK_END);

    // calculate the buffer audio size by subtracting the header
    long audio_size = ftell(input) - sizeof(header);
    int audio_block = (int) audio_size / blockSize;

    // iterate backwards through the input file audio data
    // maintain order of channels for each reversed audio block
    for (int i = audio_block - 1; i >= 0; i--)
    {
        // move block by block from end of file backwards - offset relative to the
        // start of file , which is without header
        fseek(input, sizeof(header) + i * blockSize, SEEK_SET);
        fread(buffer, blockSize, 1, input);
        fwrite(buffer, blockSize, 1, output);
    }

    // closing open files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4 - DONE
    // if "WAVE" exists in format ==> True  || else false
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
    printf("Header format signature: %s\n", header.format);
}

int get_block_size(WAVHEADER header)
{
    // TODO #7 - DONE
    int channels = header.numChannels;
    // convert bits per sample into bytes per sample
    int bytes_per_sample = header.bitsPerSample / 8;
    // size of each block is channels * bytes per sample
    int bs = channels * bytes_per_sample;
    // printf("block size: %i\n", bs);
    return bs;
}
