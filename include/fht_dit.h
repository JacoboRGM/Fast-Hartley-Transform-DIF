//header for FHT DIT 
//creator: JacoboRGM
//date 11/02/2026, 10:18am

#ifndef H_FHT_DIT_H
#define H_FHT_DIT_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void swap(double *a, double *b);

void bit_reverse(double *data, int n);

void fht_dit(double *data, int n);

void fht_get_mag(double *data, int n);

#endif  //H_FHT_DIT_H