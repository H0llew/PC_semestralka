#include "console_input.h"
#include <stdio.h>

int *get_input_indexes(int argc, char *argv[], int flags_len, char *flags[], unsigned int *err) {
    int *res, i, fl, exist;

    if (argc < 1 || !argv || flags_len <= 0 || !flags) {
        *err = 1;
        return NULL;
    }

    res = malloc(sizeof(int) * flags_len);
    if (!res) {
        *err = 2;
        return NULL;
    }

    /* vynuluj res */
    for (i = 0; i < flags_len; ++i) {
        res[i] = 0;
    }

    for (i = 1; i < argc; i += 2) {
        exist = 0;

        /* porovnej všechny přepínače z očekávanými přepínači */
        for (fl = 0; fl < flags_len; ++fl) {
            /* porovnej přepínače */
            if (strcmp(flags[fl], argv[i]) == 0) {
                exist = 1;

                /* přepínač nalezen -> existuje hodnota?*/
                if (i + 1 < argc) {
                    res[fl] = i + 1;
                    continue;
                } else {
                    res[fl] = -1;
                    continue;
                }
            }
        }

        /* přepínač nebyl nalezen */
        if (!exist) {
            *err = 0;
            return NULL;
        }
    }

    return res;
}
