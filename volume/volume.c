#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        fclose(input);  // Close input file if output file fails to open
        printf("Could not open output file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Skip header in input and output files
    fseek(input, HEADER_SIZE, SEEK_SET);
    fseek(output, HEADER_SIZE, SEEK_SET);

    // Process audio samples
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample *= factor;  // Adjust the volume
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
