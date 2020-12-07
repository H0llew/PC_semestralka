#include "reader_utils.h"

unsigned int get_line_count(FILE *file) {
    char row[MAX_ROW_LENGTH_U];
    unsigned int file_length = 0;

    if (!file)
        return 0;

    rewind(file);

    while (fgets(row, MAX_ROW_LENGTH_U, file) != NULL) {
        file_length++;
    }

    rewind(file);

    return file_length;
}

