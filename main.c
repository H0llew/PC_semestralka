#include <stdio.h>

#include "console_input.h"
#include "nodes_reader.h"

#define FLAGS_COUNT 4

int main(int argc, char *argv[]) {
    /* pro fce vracející výpis stavu */
    unsigned int err;

    /* pro vrcholy */
    node *nodes = NULL;
    unsigned int nodes_len;

    char *flags[] = {"-v", "-e", "-mst", "-mrn"};
    int *flags_value = get_input_indexes(argc, argv, FLAGS_COUNT, flags); /* TODO free */

    /* nyní je třeba zkontrolovat vstup */
    if (!flags_value) {
        /* je NULL */
    }
    /* TODO logika zpracování vstupu */

    err = read_nodes(argv[flags_value[0]], nodes, &nodes_len); /* TODO free nodes */

    return 0;
}
