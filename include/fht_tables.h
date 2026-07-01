//header for FHT TABLES LOUT
//creator: JacoboRGM
//date 12/02/2026, 11:15am

#ifndef H_FHT_TABLES_H
#define H_FHT_TABLES_H

#include <math.h>
#include <stdlib.h>

typedef struct {
    double *sin_table;
    double *cos_table;
    int size;
} FHT_Tables;

FHT_Tables precompute_fht(int n);


#endif /*H_FHT_TABLES_H*/