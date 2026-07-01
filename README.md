# Fast Hartley Transform (FHT) DIT Implementation

## Overview

This project implements a **Fast Hartley Transform (FHT)** using a **Decimation-In-Time (DIT)** algorithm to analyze the frequency content of a sampled signal.

The application:

1. Generates a synthetic multi-tone signal in the time domain.
2. Computes the Fast Hartley Transform using an optimized DIT implementation.
3. Converts the Hartley coefficients into a magnitude spectrum equivalent to the Fourier transform.
4. Displays both:
   - Time-domain waveform
   - Frequency-domain magnitude spectrum

The implementation is designed as a lightweight DSP foundation suitable for embedded systems where FFT libraries may not be available or where a real-valued transform is preferred.

FAST HARTLEY TRANSFORM (FHT) – DIT IMPLEMENTATION
1. Overview

This project implements a Fast Hartley Transform (FHT) using a Decimation-In-Time (DIT) algorithm for frequency analysis of real-valued signals.

The system:

Generates a synthetic multi-tone signal
Computes the Fast Hartley Transform (optimized DIT version)
Converts Hartley coefficients into a magnitude spectrum equivalent to FFT
Visualizes results using GNUPlot

This implementation is oriented to embedded DSP systems where efficiency and real-valued computation are important.

2. Algorithm Description
2.1 Hartley Transform

The Hartley Transform is a real-valued alternative to the Fourier Transform.

Instead of complex numbers:

X(k) = Real + j·Imag

It uses a real kernel:

cas(x) = cos(x) + sin(x)

This eliminates the need for complex arithmetic.

3. Advantages of FHT
Only real arithmetic (no complex numbers)
Lower memory usage
Faster execution in embedded systems
Suitable for DSP and microcontrollers
4. Fast Hartley Transform (DIT)

This implementation uses a Decimation-In-Time (DIT) approach.

Complexity:

O(N log2 N)

For N = 2048:

11 stages of butterfly operations
Significantly faster than O(N²) direct computation
5. Project Structure

FHT_Project/
│
├── main.c
├── fht_dit.c
├── fht_dit.h
├── fht_tables.c
├── fht_tables.h
└── README.md

6. Signal Generation

A synthetic test signal is generated with four sine waves:

60 Hz
120 Hz
180 Hz
240 Hz

Each with different amplitudes:

30 (60 Hz)
20 (120 Hz)
10 (180 Hz)
5 (240 Hz)

Mathematically:

x[n] =
30·sin(2π·60·t)

20·sin(2π·120·t)
10·sin(2π·180·t)
5·sin(2π·240·t)
7. Sampling Configuration

Number of samples:

N = 2048

Sampling interval:

sampleT = 1 / N

This defines a 1-second observation window.

Therefore:

Sampling frequency:

Fs = 2048 Hz

Frequency resolution:

Δf = Fs / N

Δf = 2048 / 2048

Δf = 1 Hz

This means each frequency bin corresponds to 1 Hz resolution, allowing precise detection of harmonic components.

8. Execution Flow
Generate synthetic signal
Plot time-domain waveform
Precompute FHT tables
Execute Fast Hartley Transform (DIT)
Convert result to magnitude spectrum
Plot frequency-domain result
9. FHT Table Precomputation

Before executing the transform:

FHT_Tables tables = precompute_fht(N);

These tables store:

Twiddle factors
Index mappings
Butterfly optimization values

This improves performance by avoiding repeated calculations.

10. Transform Execution

The transform is applied in-place:

fht_dit_optimized(data, N, &tables);

Before:

Time domain signal

After:

Hartley frequency coefficients
11. Magnitude Spectrum Conversion

The Hartley output is converted into a Fourier-equivalent magnitude spectrum:

|X(k)| =
(2/N) * sqrt( (H(k)² + H(N-k)²) / 2 )

Only bins from:

k = 0 to N/2

are used due to symmetry.

12. Visualization (GNUPlot)

The program uses GNUPlot via pipe:

popen("gnuplot -persistent", "w");

Two plots are generated:

12.1 Time Domain Plot

Shows amplitude vs time of the generated signal.

12.2 Frequency Spectrum

Shows magnitude vs frequency.

Expected peaks:

60 Hz
120 Hz
180 Hz
240 Hz
13. Example Output Interpretation

The spectrum should clearly show 4 peaks corresponding to the input sine waves.

This validates:

Correct sampling
Correct FHT implementation
Correct magnitude reconstruction
14. Compilation

Compile with:

gcc main.c fht_dit.c fht_tables.c -lm

15. Dependencies
C compiler (GCC recommended)
math.h
stdint.h
GNUPlot installed
16. Performance Notes

For embedded systems, improvements can include:

Replace double with float
Use fixed-point arithmetic (Q15/Q31)
Store tables in Flash memory
Use DMA for input acquisition
Optimize butterfly stages for SIMD or DSP instructions
17. Applications

This implementation can be used in:

Power quality analysis
Harmonic detection
Audio signal processing
Vibration analysis
Motor diagnostics
Embedded real-time spectrum analysis
18. Summary

This project demonstrates a complete DSP pipeline:

Signal generation → Sampling → Fast Hartley Transform → Spectrum reconstruction → Frequency analysis

It is designed as a lightweight alternative to FFT-based systems for real-valued embedded applications.


