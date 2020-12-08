#include <stdio.h>

#include "console_input.h"
#include "nodes_reader.h"
#include "edges_reader.h"

#define FLAGS_COUNT 4

#define ERROR_WRONG_ARGS "Illegal argument exeption!\nAllowed parameters -> -e -v- mst -mrn\n"
#define ERROR_WRONG_F_PAR "Wrong function arguments\n"
#define ERROR_INSF_MEM "Memory error!\nCannot allocate memory!\n"
#define ERROR_FATAL "Fatal error!\n"

#define ERROR_NODES_FILE "Invalid vertex file.\n"
#define ERROR_EDGES_FILE "Invalid edge file.\n"

int main(int argc, char *argv[]) {
    /* pro fce vracející výpis stavu */
    unsigned int err;
    /* pro vrcholy */
    node *nodes = NULL;
    int nodes_len = 0;
    /* pro hrany */
    edge *edges = NULL;
    int edge_len = 0;

    /* přečtení vstupu z konzole */
    char *flags[] = {"-v", "-e", "-mst", "-mrn"};
    int *flags_value = get_input_indexes(argc, argv, FLAGS_COUNT, flags, &err); /* TODO free */
    /* nyní je třeba zkontrolovat vstup */
    if (!flags_value) {
        if (err == 0)
            printf(ERROR_WRONG_ARGS);
        else if (err == 1) {
            printf(ERROR_WRONG_F_PAR);
        } else if (err == 2) {
            printf(ERROR_INSF_MEM);
        } else {
            printf(ERROR_FATAL);
        }
        return -1;
    }

    /* zkontroluj povinné přepínače */

    /* vrcholy */
    if (flags_value[0] <= 0) {
        printf(ERROR_NODES_FILE);
        return 1;
    } else {
        /* načti vrcholy */
        err = 0;
        err = read_nodes(argv[flags_value[0]], &nodes, &nodes_len);
        if (err == 1 || err == 3) {
            printf(ERROR_NODES_FILE);
            return 2;
        }
    }

    /* hrany */
    if (flags_value[1] <= 0) {
        printf(ERROR_EDGES_FILE);
        return 2;
    } else {
        /* načti hrany */
        err = 0;
        err = read_edges(argv[flags_value[1]], &edges, &edge_len);
        if (err == 1 || err == 3) {
            printf(ERROR_EDGES_FILE);
            return 2;
        }
    }

    printf("%d \n", nodes_len);
    printf("%d \n", edge_len);

    return 0;
}
