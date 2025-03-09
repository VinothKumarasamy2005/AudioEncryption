#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;

#define FRAME_SIZE 16
#define DT 0.01  // Time step for Euler method

// Chen's Hyperchaotic System Parameters
const double alpha = 36.0, gamm = 28.0, epsilon = 0.2, sigma = 16.0, beta = 3.0;
const double x_init = 0.0, y_init = 0.01, z_init = 0.01, w_init = 0.0;

// ---------------------------------------------------------------------------------
// Generate Chaotic Sequence using Chen's 4D Hyperchaotic System
void generateChen4DSequence(double chaoticSequence[FRAME_SIZE]) {
    double x = x_init, y = y_init, z = z_init, w = w_init;

    for (int i = 0; i < FRAME_SIZE / 4; i++) {  // Generate 4 values per iteration
        double dx = alpha * (y - x);
        double dy = sigma * x - x * z + gamm * y - w;
        double dz = x * y - beta * z;
        double dw = x - epsilon;

        x += dx * DT;
        y += dy * DT;
        z += dz * DT;
        w += dw * DT;

        chaoticSequence[i * 4] = x;
        chaoticSequence[i * 4 + 1] = y;
        chaoticSequence[i * 4 + 2] = z;
        chaoticSequence[i * 4 + 3] = w;
    }
}

// ---------------------------------------------------------------------------------
// Haar Discrete Wavelet Transform (DWT)
void haarDWT4(const int signal[FRAME_SIZE], double coeffs[FRAME_SIZE]) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        coeffs[i] = static_cast<double>(signal[i]);
    }

    for (int step = FRAME_SIZE; step > 1; step /= 2) {
        double temp[FRAME_SIZE] = {0.0};
        for (int i = 0; i < step / 2; i++) {
            temp[i] = (coeffs[2 * i] + coeffs[2 * i + 1]) / sqrt(2.0);
            temp[step / 2 + i] = (coeffs[2 * i] - coeffs[2 * i + 1]) / sqrt(2.0);
        }
        for (int i = 0; i < step; i++) {
            coeffs[i] = temp[i];
        }
    }
}

// ---------------------------------------------------------------------------------
// Chaotic Permutation Algorithm
void chaoticPermutation(const double inputSignal[FRAME_SIZE], double outputSignal[FRAME_SIZE], double chaoticSequence[FRAME_SIZE]) {
    int m = FRAME_SIZE;
    double xperm = chaoticSequence[0];

    if (xperm > 0) {
        // Case 1: Reverse entire signal
        for (int i = 0, j = m - 1; i < m; i++, j--) {
            outputSignal[i] = inputSignal[j];
        }
    } else {
        // Case 2: Reverse both halves separately
        int half = m / 2;

        // Reverse first half
        for (int i = 0; i < half; i++) {
            outputSignal[i] = inputSignal[half - 1 - i];
        }

        // Reverse second half
        for (int i = half; i < m; i++) {
            outputSignal[i] = inputSignal[m - 1 - (i - half)];
        }
    }
}

// ---------------------------------------------------------------------------------
// Multiply Transformed Signal with Chaotic Sequence
void multiplySignals(const double transformedSignal[FRAME_SIZE], const double chaoticSequence[FRAME_SIZE], double result[FRAME_SIZE]) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        result[i] = transformedSignal[i] * chaoticSequence[i];
    }
}

// ---------------------------------------------------------------------------------
// Complete Encryption Function
void encryfinal(const int speechSignal[FRAME_SIZE], double encryptedSignal[FRAME_SIZE]) {
    #pragma HLS INTERFACE s_axilite port=speechSignal bundle=control
    #pragma HLS INTERFACE s_axilite port=encryptedSignal bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control

    // If using BRAM, set address width to 12 bits
    #pragma HLS INTERFACE bram port=speechSignal depth=4096 // 12-bit addressable memory
    #pragma HLS INTERFACE bram port=encryptedSignal depth=4096 // 12-bit addressable memory

    double transformedSignal[FRAME_SIZE];
    double chaoticSequence[FRAME_SIZE];
    double multipliedSignal[FRAME_SIZE];

    // Perform Haar DWT
    haarDWT4(speechSignal, transformedSignal);

    // Generate Chaotic Sequence
    generateChen4DSequence(chaoticSequence);

    // Step 1: Multiply Transformed Signal with Chaotic Sequence
    multiplySignals(transformedSignal, chaoticSequence, multipliedSignal);

    // Step 2: Perform Chaotic Permutation
    chaoticPermutation(multipliedSignal, encryptedSignal, chaoticSequence);
}

