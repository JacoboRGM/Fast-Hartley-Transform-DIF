#include "fht_dit.h"
#include "fht_tables.h"


// 1. exchange for values a and b
void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

// 2. bit reversal function
void bit_reverse(double *data, int n) {
    int i, j, k;
    for (i = 1, j = 0; i < n; i++) {
        for (k = n >> 1; k > (j ^= k); k >>= 1);
        if (i < j) swap(&data[i], &data[j]);
    }
}

//deprecated//
// 3. Algorithim of Hsieh S. Hou (FHT)
void fht_dit(double *data, int n) {
    int i, j, k, step, half;
    double a, b, c, s, angle;

    bit_reverse(data, n);

    for (i = 0; i < n; i += 2) {
        a = data[i];
        b = data[i + 1];
        data[i] = a + b;
        data[i + 1] = a - b;
    }

    for (step = 4; step <= n; step <<= 1) {
        half = step >> 1;
        int quarter = step >> 2;
        angle = 2.0 * M_PI / step;

        for (i = 0; i < n; i += step) {
            a = data[i];
            b = data[i + half];
            data[i] = a + b;
            data[i + half] = a - b;

            if (quarter > 0) {
                a = data[i + quarter];
                b = data[i + half + quarter];
                data[i + quarter] = a + b;
                data[i + half + quarter] = a - b;
            }

            for (j = 1; j < quarter; j++) {
                c = cos(j * angle);
                s = sin(j * angle);
                int idx1 = i + j;
                int idx2 = i + half - j;
                int idx3 = i + half + j;
                int idx4 = i + step - j;

                a = data[idx3] * c + data[idx4] * s;
                b = data[idx3] * s - data[idx4] * c;
                data[idx3] = data[idx1] - a;
                data[idx1] += a;
                data[idx4] = data[idx2] - b;
                data[idx2] += b;
            }
        }
    }
}

//3.1 Algorithm of Hsieh S. Hou (FHT), eficiently on compute use LOUP
void fht_dit_optimized(double *data, int n, FHT_Tables *tables) {
    int i, j, k, step, half;
    double a, b, c, s;

    bit_reverse(data, n);

    // Mariposa base (step 2)
    for (i = 0; i < n; i += 2) {
        a = data[i];
        b = data[i + 1];
        data[i] = a + b;
        data[i + 1] = a - b;
    }

    for (step = 4; step <= n; step <<= 1) {
        half = step >> 1;
        int quarter = step >> 2;
        
        // El salto en la tabla depende de cuánto se reduce el step respecto a n
        // Si n=1024 y step=4, el salto es 256.
        int table_step = tables->size / step; 

        for (i = 0; i < n; i += step) {
            // Caso j = 0
            a = data[i];
            b = data[i + half];
            data[i] = a + b;
            data[i + half] = a - b;

            if (quarter > 0) {
                a = data[i + quarter];
                b = data[i + half + quarter];
                data[i + quarter] = a + b;
                data[i + half + quarter] = a - b;
            }

            // Bucle con valores precomputados
            for (j = 1; j < quarter; j++) {
                // Acceso directo a memoria en lugar de funciones trigonométricas
                c = tables->cos_table[j * table_step];
                s = tables->sin_table[j * table_step];

                int idx1 = i + j;
                int idx2 = i + half - j;
                int idx3 = i + half + j;
                int idx4 = i + step - j;

                a = data[idx3] * c + data[idx4] * s;
                b = data[idx3] * s - data[idx4] * c;
                
                data[idx3] = data[idx1] - a;
                data[idx1] += a;
                data[idx4] = data[idx2] - b;
                data[idx2] += b;
            }
        }
    }
}

// 4. Conversión a Magnitud
void fht_get_mag(double *data, int n) {

    double coeff_norm = (double)(2/(double)n);

    // 1. Guardamos los valores especiales antes de empezar el bucle
    double dc = fabs(data[0]);
    double nyquist = fabs(data[n / 2]);

    // 2. Procesamos solo la mitad del espectro + 1
    // La magnitud es simétrica, así que calculamos una vez y copiamos
    for (int k = 1; k < n / 2; k++) {
        int k_rev = n - k;
        
        double hk = data[k];
        double hkr = data[k_rev];

        // Fórmula de Hartley a Magnitud de Fourier
        double mag = coeff_norm*sqrt((hk * hk + hkr * hkr) / 2.0);

        // Si quieres la magnitud bruta (36, 10.45...), NO uses coeff_norm.
        // Si quieres la amplitud real (10, 5...), multiplica por (2.0/n).
        data[k] = mag; 
        data[k_rev] = mag; // Simetría
    }

    // 3. Asignamos los valores especiales al final
    data[0] = dc;
    data[n / 2] = nyquist;
}