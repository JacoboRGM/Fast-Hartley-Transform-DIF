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

---

# Algorithm Description

## Hartley Transform

The Hartley Transform is a real-valued equivalent of the Fourier Transform.

Unlike the FFT, which produces complex outputs:

\[
X(k)=Re(X(k))+jIm(X(k))
\]

the FHT produces only real coefficients:

\[
H(k)
\]

The Hartley transform uses the kernel:

\[
cas(x)=cos(x)+sin(x)
\]

which eliminates the need for complex arithmetic.

For real-valued signals, this provides advantages:

- Reduced memory usage
- No complex data structures
- Efficient implementation on microcontrollers/DSPs

---

# Fast Hartley Transform (FHT)

The implemented algorithm uses:

## Decimation In Time (DIT)

The DIT approach recursively decomposes the input signal into smaller blocks until butterfly operations can be applied.

The computational complexity is:

\[
O(Nlog_2(N))
\]

instead of the direct transform:

\[

O(N^2)
\]

For:


the transform requires:

\[
2048 \times 11
\]

butterfly stages.

---

# Project Structure

