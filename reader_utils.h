#ifndef READER_UTILS_H
#define READER_UTILS_H

#include <stdio.h>

#define MAX_ROW_LENGTH_U 15000


/**
 * Zjistí a vrátí počet řádků souboru
 *
 * @param file soubor
 * @return 0 -> pokud soubor má 0 řádek, nebo nastala chyba, jinak vrátí počet řádek
 */
unsigned int get_line_count(FILE *file);

#endif
