#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <stdlib.h>
#include <string.h>

/**
 * Funkce prochází vstupní pole "argv" a hledá v něm hodnoty přepínačů zadaných ve "flags".
 * Pozice nalezených pozic ve vraceném poli odpovídá pozici přepínače ve "flags".
 * Možné hodnoty výstupního pole jsou:  -1 => přepínač nebyl zadán s hodnotou
 *                                       0 => přepínač nebyl zadán
 *                                      >0 => pozice hledané hodnoty přepínače
 * @param argc velikost pole "argc"
 * @param argv vstupní pole s přepínači a jejich hodnotami
 * @param flags_len velikost pole "flags"
 * @param flags pole hledaných přepínačů
 * @param err příkaz pro výpis chyby
 * @return pole pozic hodnot přepínačů na idexu odpovídající pozici přepínače ve "flags",
 *         nebo null pokud byly zadány neplatné parametry, nebo neznámý přepínač
 */
int *get_input_indexes(int argc, char *argv[], int flags_len, char *flags[], unsigned int *err);

#endif
