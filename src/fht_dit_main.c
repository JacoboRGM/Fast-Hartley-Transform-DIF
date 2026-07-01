#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "fht_dit.h"
#include "fht_tables.h"

//size fo FHT
#define N 2048

double data[N];

void plot_fht(double *x, int n, double fs);

void plot_signal(double *x, int n, double fs);


int main(void){

    // Biuld a signal in data buffer
    // N muestras en un segundo
    double sampleT = (double)(1 / (double)N);
    for (int index = 0; index < N; index++)
    {

        data[index] = 30 * sin(2 * M_PI * 60 * sampleT * index) + 
                        20 * sin(2 * M_PI * 120 * sampleT * index) + 
                        10 * sin(2 * M_PI * 180 * sampleT * index)+
                        5 * sin(2 * M_PI * 240 * sampleT * index);
    }

    plot_signal((double *)data, N, sampleT);
    getchar();  // pausa

    // Frist, calculate LOUP
    FHT_Tables FHT_DIT_TABLES = precompute_fht((int)N);
    //second, compute FHT
    fht_dit_optimized((double *)data, (int)N, &FHT_DIT_TABLES);

    plot_fht((double *)data, N, sampleT);
    getchar();
    return 0;
}

void plot_signal(double *x, int n, double fs)
{
    FILE *gp = popen("gnuplot -persistent", "w");

    fprintf(gp, "set term windows 0\n");
    fprintf(gp, "set title 'Señal en el tiempo'\n");
    fprintf(gp, "set xlabel 'Tiempo (s)'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot '-' with lines\n");

    for(int i=0;i<n;i++)
    {
        double t = (double)i / fs;
        fprintf(gp,"%f %f\n", t, x[i]);
    }

    fprintf(gp,"e\n");
    fflush(gp);
    pclose(gp);
}


void plot_fht(double *x, int n, double fs)
{
    FILE *gp = popen("gnuplot -persistent", "w");

    fprintf(gp, "set term windows 1\n");
    fprintf(gp, "set title 'Magnitud FHT'\n");
    fprintf(gp, "set xlabel 'Frecuencia (Hz)'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot '-' with lines\n");

    //compute coefficient of normalization
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

    for (int k = 0; k <= n / 2; k++)
    {

        fprintf(gp, "%f\n", data[k]);
    }

    fprintf(gp,"e\n");
    fflush(gp);
    pclose(gp);
}
