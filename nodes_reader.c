#include "nodes_reader.h"

unsigned int read_nodes(char *file_name, node *output, unsigned int *node_len) {
    /* čtení */
    FILE *file;
    unsigned int file_length;
    char row[MAX_SZ_LENGTH];
    unsigned int count;
    /* vrcholy */
    node *res = NULL;

    /* ověř vstup */
    if (!file_name)
        return 4;

    /* otevři soubor */
    file = fopen(file_name, "r");
    if (!file)
        return 1;

    /* zjisti počet řádek souboru */
    file_length = get_line_count(file);
    if (file_length == 0)
        return 2;

    /* malloc node */
    res = malloc(sizeof(node) * file_length);
    if (!res)
        return 3;

    /* projdi a zpracuj soubor */
    count = 0;
    while (fgets(row, MAX_SZ_LENGTH, file) != NULL) {
        if (count == 0) {
            /* zkontroluj hlavičku */
            if (strcmp(row, FILE_HEADER) == 0)
                return 2;
            count++;
            continue;
        }

        node *curr = process_row(row);
        if (!curr) {
            /* nevalidní soubor! */
            free(res);
            return 2;
        }
        /* TODO dups */
        res[count] = *curr;
        count++;
    }

    fclose(file);

    /* free */
    free(res);

    return 0;
}

node *process_row(char *line) {
    unsigned int step = 0;
    char *wkt_token, *p_end, cpy[MAX_SZ_LENGTH];
    double x, y;
    unsigned int id;

    char *token = strtok(line, ",");

    /* 3 kroky (WTD, id a nakonec sname) */
    while (token != NULL) {
        printf(" %s\n", token);
        token = strtok(NULL, ",");
    }

    return NULL;
}
