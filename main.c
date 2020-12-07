#include <stdio.h>

#include "console_input.h"
#include "nodes_reader.h"
#include "edges_reader.h"

#define FLAGS_COUNT 4

int main(int argc, char *argv[]) {
    /* pro fce vracející výpis stavu */
    unsigned int err;

    /* pro vrcholy */
    node *nodes = NULL;
    int nodes_len;
    /* pro hrany */
    edge *edges = NULL;
    int edge_len;

    int i = 0;

    char *flags[] = {"-v", "-e", "-mst", "-mrn"};
    int *flags_value = get_input_indexes(argc, argv, FLAGS_COUNT, flags); /* TODO free */

    /* nyní je třeba zkontrolovat vstup */
    if (!flags_value) {
        /* je NULL */
    }
    /* TODO logika zpracování vstupu */

    /* err = read_nodes(argv[flags_value[0]], &nodes, &nodes_len); */ /* TODO free nodes */

    /*
    if (!nodes) {
        printf("WHY");
    }

    for (i = 0; i < nodes_len; ++i) {
        printf("%d \n", nodes[i].id);
    }

    return err;
    */

    read_edges(argv[flags_value[1]], &edges, &edge_len);

    return 0;
}
