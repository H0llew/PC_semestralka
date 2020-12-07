#ifndef EDGES_READER_H
#define EDGES_READER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "reader_utils.h"

/** hlavička souboru 1 */
#define FILE_HEADER_EDGES_1 "WKT,id,nation,cntryname,source,target,clength,,,,,,,,,,,,,,,,,,\n"
/** hlavička souboru 2 */
#define FILE_HEADER_EDGES_2 "WKT,id,nation,cntryname,source,target,clength\n"
/** maximální délka jednoho řádku souboru s hranama */
#define MAX_SZ_EDGE_LENGTH 20000
/** maximální délka WKT (max. délka v datech byla ~12500)*/
#define MAX_WKT_LENGTH 15000
/** maximální délka pro ostatní data */
#define MAX_REST_LENGTH 5000
/** maximální název státu */
#define MAX_NATION_NAME 100
/** počet prohledávaných sloupců řádku */
#define EDGE_COLUMNS 7

/**
 * \struct hrana
 * \brief Struktura představující hranu (hrana železniční sítě).
 */
typedef struct edge_t {
    char WKT[MAX_WKT_LENGTH];
    unsigned int id;
    unsigned int nation_id;
    char nation_name[MAX_NATION_NAME];
    unsigned int source;
    unsigned int target;
    double length;
} edge;

/**
 * Zpracuje soubor "file_name" a pokud jsou data souboru validní vrátí je v podobě pole struktur "edge" o délce "edge_len".
 *
 * @param file_name název souboru
 * @param output výstupní pole hran
 * @param edge_len délka výstupního pole hran
 * @param maxIdOfNodes nejvyšší id vrcholu
 * @return <ul>
 *          <li> 0 -> pokud vše proběhlo v pořádku </li>
 *          <li> 1 -> pokud nebyl nalezen soubor </li>
 *          <li> 2 -> pokud nejsou platné atributy   </li>
 *          <li> 3 -> pokud se nepodařilo přiřadit paměť </li>
 *         </ul>
 */
unsigned int read_edges(char *file_name, edge **output, int *edge_len, unsigned int maxId);

/**
 * Zpracuje načtenou řádku na strukturu "edge".
 * @param line řádka pro zpracování
 * @param flag přiřadí do paměti 1, pokud nešla přiřadit paměť, jinak 0
 * @return vrchol reprezentující hranu železniční sítě, jinak NULL
 */
edge *process_edge_row(char *line, int *flag);

unsigned int *create_matrix(unsigned int size);

unsigned int check_edge(unsigned int source, unsigned int target);

#endif
