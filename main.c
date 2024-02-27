#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

int main(int argc, char **argv)
{
    (void)argc;
    assert(*argv != NULL);
    char *program = *argv++;

    if (*argv == NULL)
    {
        fprintf(stderr, "Usage: %s <input.png>\n", program);
        fprintf(stderr, "ERROR: no input file is provided\n");
        exit(1); // exit with error code (1)
    }

    const char *input_file_path = *argv++;
    FILE *input_file = fopen(input_file_path, "rb");

    if (input_file == NULL)
    {
        fprintf(stderr, "ERROR: cannot open file '%s': %s\n", input_file_path, strerror(errno));
        exit(1); // exit with error code (1)
    }

    uint8_t header[8];
    size_t header_size = fread(header, 1, sizeof(header), input_file);

    if (header_size != sizeof(header))
    {
        fprintf(stderr, "ERROR: cannot read header from file '%s': %s\n", input_file_path, strerror(errno));
        exit(1); // exit with error code (1)
    }

    const uint8_t png_header[] = {137, 80, 78, 71, 13, 10, 26, 10};

    if (memcmp(header, png_header, sizeof(png_header)) != 0)
    {
        fprintf(stderr, "ERROR: file '%s' is not a PNG file\n", input_file_path);
        exit(1); // exit with error code (1)
    }

    for (size_t i = 0; i < sizeof(header); i++)
    {
        printf("%u ", header[i]);
    }

    printf("\n");

    fclose(input_file);

    return 0;
}
