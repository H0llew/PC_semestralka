#include "nodes_reader.h"

unsigned int read_nodes(char *file_name, node **output, int *node_len) {
    /* čtení */
    FILE *file;
    unsigned int file_length;
    char row[MAX_SZ_LENGTH];
    unsigned int count;
    int actPos = 0;
    int err = 0;
    /* vrcholy */
    node *res = NULL;
    node *curr = NULL;

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
    res = malloc(sizeof(node) * (file_length - 1)); /* -1 protože header */
    if (!res)
        return 3;

    /* projdi a zpracuj soubor */
    count = 0;
    actPos = 0;
    while (fgets(row, MAX_SZ_LENGTH, file) != NULL) {
        if (count == 0) {
            /* zkontroluj hlavičku */
            if (strcmp(row, FILE_HEADER) == 0)
                return 2;
            count++;
            continue;
        }

        curr = process_node_row(row, &err);
        if (!curr) {
            /* TODO pamět */
            return 2;
        }
        if (err == 1) {
            /* TODO pamět */
            return 3;
        }

        /* potřebuju minimálně 2 prvky */
        if (actPos > 0) {
            /* zkontroluj zda nemají stejné id */
            if (res[actPos - 1].id == (*curr).id)
                continue; /* SKIP -> id jsou stejné */
            res[actPos] = *curr;
            /* printf("T %u \n", res[actPos - 1].id); */
        } else {
            res[actPos] = *curr;
            /* printf("T %u \n", res[actPos].id); */
        }

        count++;
        actPos++;
    }

    /*
    for (count = 0; count < actPos; ++count) {
        printf("%u \n", res[count].id);
    }
     */

    /* vytvoř výstup output */
    /* printf("%d", actPos); */
    *output = malloc(sizeof(node) * actPos);
    if (!(*output)) {
        return 3;
    }

    memcpy(*output, res, sizeof(node) * actPos);
    *node_len = actPos;

    /*
    for (actPos = 0; actPos < *node_len; ++actPos) {
        printf("%u \n", output[actPos].id);
    }
    */

    /* ukonči a uvolni paměť */

    fclose(file);
    /* TODO free */
    /* free(res); */

    return 0;
}

node *process_node_row(char *line, int *flag) {
    unsigned int step = 0;
    char *wkt_token, *p_end, *p_end2;
    char cols[COLUMNS][MAX_SZ_LENGTH];
    /* prvky vrcholu */
    double x, y;
    unsigned int id;
    /* vrchol */
    node *n = NULL;

    char *token = strtok(line, ",");

    /* 3 kroky (WTD, id a nakonec sname) */
    while (token != NULL) {
        if (step >= COLUMNS)
            return NULL;

        strcpy(cols[step], token);

        token = strtok(NULL, ",");
        step++;
    }
    if (step < 2)
        return NULL;
    /* zkontroluj zda nebyl zadán název stanice */
    if (step == 2)
        strcpy(cols[2], "");

    /* zpracuj prvky "cols" */
    /* WKT */
    wkt_token = strtok(cols[0], "(");
    wkt_token = strtok(NULL, ")");

    /* d1 */
    x = strtod(wkt_token, &p_end);
    if (x == 0 && (errno != 0 || p_end == wkt_token))
        return NULL;
    /* d2 */
    y = strtod(p_end, &p_end2);
    if (y == 0 && (errno != 0 || p_end2 == p_end))
        return NULL;

    /* id */
    id = strtol(cols[1], &p_end, 10);
    if (id == 0 && (errno != 0 || p_end == cols[1]))
        return NULL;

    n = malloc(sizeof(node));
    if (!n) {
        *flag = 1;
        return NULL;
    }

    n->width = x;
    n->length = y;
    n->id = id;
    strcpy(n->name, cols[2]);

    return n;
}
