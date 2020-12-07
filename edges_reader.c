#include "edges_reader.h"

unsigned int read_edges(char *file_name, edge **output, int *edge_len, unsigned const int maxId) {
    FILE *file;
    unsigned int file_length;
    edge *rows = NULL, *curr = NULL;
    int actEdge, err = 0;
    char row[MAX_SZ_EDGE_LENGTH];

    /* kontrola parametrů */
    if (!file_name || !output || !edge_len)
        return 2;

    /* otevři soubor */
    file = fopen(file_name, "r");
    if (!file)
        return 1;

    /* zjisti počet řádků v souboru */
    file_length = get_line_count(file);
    if (file_length < 2) /* soubor jen s hlavičkou asi smysl nedává */
        return 2;

    /* přiřaď pamět potřebnou pro zpracování a načtení všech řádků */
    rows = malloc(sizeof(edge) * file_length);
    if (!rows)
        return 3;

    /* zkontroluj hlavičku souboru */
    fgets(row, MAX_SZ_EDGE_LENGTH, file); /* nebude NULL */
    if ((strcmp(row, FILE_HEADER_EDGES_1) != 0) && (strcmp(row, FILE_HEADER_EDGES_2) != 0)) {
        free(rows);
        return 2;
    }

    /* projdi a zpracuj data souboru */
    actEdge = 0;
    while (fgets(row, MAX_SZ_EDGE_LENGTH, file) != NULL) {
        curr = process_edge_row(row, &err);
        if (!curr) {
            if (err == 1)
                return 3;
            return 2;
        }

        /* vyfiltruj špatná data */
        if (actEdge > 0) {
            /* id duplicita */
            if (rows[actEdge - 1].id == curr->id)
                continue;
            /* 0 délka */
            if (curr->length == 0)
                continue;
            /* hrana je buď {u,u} a nebo už existuje */

        }

        rows[actEdge] = *curr;

        actEdge++;
    }

    printf("%d", actEdge);

    return 0;
}

edge *process_edge_row(char *line, int *flag) {
    int col, i;
    char wkt[MAX_WKT_LENGTH] = {0}, cols_value[EDGE_COLUMNS - 1][MAX_REST_LENGTH];
    edge *res;
    char *p_end;
    /* prvky hrany */
    unsigned int id, nation_id, source, target;
    double length;

    /* pro rozdělení řádky */
    char *token = NULL;

    /* ověření parametrů */
    if (!line || !flag)
        return NULL;

    /* dostaň WKT */
    token = strtok(line, "\"");
    if (!token)
        return NULL;
    strcpy(wkt, token);

    /* nyní můžeme oddělovat pomocí čárek */
    for (col = 1; col < EDGE_COLUMNS; ++col) {
        if (token == NULL) {
            --col;
            break;
        }

        token = strtok(NULL, ",");
        if (strcmp(token, "\n") == 0) {
            --col;
            break;
        }

        strcpy(cols_value[col - 1], token);
        /* printf("%d %s \n", col - 1, token); */
    }
    /* kontrola parsovaných dat */
    if (col < (EDGE_COLUMNS - 2)) {
        /* špatná data */
        return NULL;
    }
    if (col < EDGE_COLUMNS - 1) {
        /* pravděpodobně nebyl zadán stát (snad jen ten nemůže být zadán )*/
        /* posuň prvky o 1 => od sname */
        for (i = EDGE_COLUMNS - 2; i >= 2; --i) {
            strcpy(cols_value[i], cols_value[i - 1]);
        }
        strcpy(cols_value[2], "");
    }

    id = strtol(cols_value[0], &p_end, 10);
    if (id == 0 && (errno != 0 || p_end == cols_value[0]))
        return NULL;

    nation_id = strtol(cols_value[1], &p_end, 10);
    if (nation_id == 0 && (errno != 0 || p_end == cols_value[1]))
        return NULL;

    source = strtol(cols_value[3], &p_end, 10);
    if (source == 0 && (errno != 0 || p_end == cols_value[3]))
        return NULL;

    target = strtol(cols_value[4], &p_end, 10);
    if (target == 0 && (errno != 0 || p_end == cols_value[4]))
        return NULL;

    length = strtod(cols_value[5], &p_end);
    if (length == 0 && (errno != 0 || p_end == cols_value[5]))
        return NULL;

    /* vytvoř hranu a vlož do ní data */
    res = malloc(sizeof(edge));
    if (!res) {
        *flag = 1;
        return NULL;
    }

    strcpy(res->WKT, wkt);
    res->id = id;
    res->nation_id = nation_id;
    strcpy(res->nation_name, cols_value[2]);
    res->source = source;
    res->target = target;
    res->length = length;

    /* kontrolní výpis */
    /*
    for (i = 0; i < EDGE_COLUMNS - 1; ++i) {
        printf("%s \n", cols_value[i]);
    }
    printf("K %d \n", col);
    printf("K %s \n", wkt);
    */

    return res;
}
