#include "fht_tables.h"
#include "fht_dit.h"

FHT_Tables precompute_fht(int n) {
    FHT_Tables tables;
    int max_quarter = n / 4;
    tables.size = n;
    tables.sin_table = (double *)malloc(max_quarter * sizeof(double));
    tables.cos_table = (double *)malloc(max_quarter * sizeof(double));

    // Usamos el ángulo base más pequeño para llenar la tabla
    // El ángulo máximo j * (2*PI/step) ocurre cuando j = quarter-1 y step=n
    double angle_step = 2.0 * M_PI / n;
    for (int j = 0; j < max_quarter; j++) {
        tables.sin_table[j] = sin(j * angle_step);
        tables.cos_table[j] = cos(j * angle_step);
    }
    return tables;
}