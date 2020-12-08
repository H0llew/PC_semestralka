#ifndef NODES_READER_H
#define NODES_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "reader_utils.h"

/** maximální délka názvu stanice (snad postačí). */
#define MAX_STATION_NAME 255
/** hlavička souboru */
#define FILE_NODES_HEADER "WKT,id,sname\n"
/** maximální délka jednoho řádku souboru s vrcholy */
#define MAX_SZ_NODES_LENGTH 1000
/** počet sloupců v souboru */
#define COLUMNS 3

/**
 * \struct vrchol
 * \brief Struktura představující vrchol (stanici).
 */
typedef struct node_t {
    double width;
    double length;
    unsigned int id;
    char name[MAX_STATION_NAME];
} node;

/**
 * Zpracuje soubor "file_name" a pokud jsou data souboru validní vrátí je v podobě pole struktur "node" o délce "node_len".
 *
 * @param file_name název souboru
 * @param output výstupní pole vrcholů
 * @param node_len délka výstupního pole vrcholů
 * @return <ul>
 *          <li> 0 -> pokud vše proběhlo v pořádku </li>
 *          <li> 1 -> pokud nebyl nalezen soubor </li>
 *          <li> 2 -> pokud nejsou platné parametry funkce  </li>
 *          <li> 3 -> pokud se nepodařilo soubor načíst </li>
 *          <li> 4 -> pokud se nepodařilo přiřadit paměť </li>
 *         </ul>
 */
unsigned int read_nodes(char *file_name, node **output, int *node_len);

/**
 * Zpracuje načtenou řádku na strukturu "node".
 * @param line řádka pro zpracování
 * @param přiřadí do paměti 1, pokud nešla přiřadit paměť
 * @return vrchol reprezentující stanici, jinak NULL
 */
node *process_node_row(char *line, int *flag);

#endif
