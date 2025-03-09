#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>

using namespace std;

#define FRAME_SIZE 16
#define DT 0.01  // Time step for Euler method

// Chen's Hyper chaotic System Parameters
const double alpha = 36.0, gamma = 28.0, epsilon = 0.2, sigma = 16.0, beta = 3.0;
// Initial Conditions (Fixed Variable Name Conflict)
const double x_init = 0.0, y_init = 0.01, z_init = 0.01, w_init = 0.0;

// ---------------------------------------------------------------------------------
// Chen's 4D Hyperchaotic System (Generates exactly 16 elements in [x1,y1,z1,w1,...])
vector<double> generateChen4DSequence(int length) {
    double x = x_init, y = y_init, z = z_init, w = w_init;
    vector<double> chaoticSequence;

    for (int i = 0; i < length / 4; i++) {  // Generate 4 values per iteration
        double dx = alpha * (y - x);
        double dy = sigma * x - x * z + gamma * y - w;
        double dz = x * y - beta * z;
        double dw = x - epsilon;

        x += dx * DT;
        y += dy * DT;
        z += dz * DT;
        w += dw * DT;

        chaoticSequence.push_back(x);
        chaoticSequence.push_back(y);
        chaoticSequence.push_back(z);
        chaoticSequence.push_back(w);
    }
    return chaoticSequence;
}

// ---------------------------------------------------------------------------------
// Haar Discrete Wavelet Transform (4-level DWT)
vector<int16_t> haarDWT4(const vector<int>& signal) {
    int N = signal.size();
    vector<double> coeffs(signal.begin(), signal.end());

    for (int step = N; step > 1; step /= 2) {
        vector<double> temp(step, 0.0);
        for (int i = 0; i < step / 2; i++) {
            temp[i] = (coeffs[2 * i] + coeffs[2 * i + 1]) / sqrt(2.0);
            temp[step / 2 + i] = (coeffs[2 * i] - coeffs[2 * i + 1]) / sqrt(2.0);
        }
        for (int i = 0; i < step; i++) {
            coeffs[i] = temp[i];
        }
    }

    vector<int16_t> quantized(coeffs.size());
    for (size_t i = 0; i < coeffs.size(); i++) {
        quantized[i] = static_cast<int16_t>(round(coeffs[i]));
    }
    return quantized;
}

// ---------------------------------------------------------------------------------
// XOR Masking with Chaotic Sequence (Corrected to Ensure 8-bit Output)
vector<uint8_t> bitwiseXOR(const vector<int16_t>& transformedSignal, const vector<double>& chaoticSequence) {
    vector<uint8_t> result(FRAME_SIZE);
    for (int i = 0; i < FRAME_SIZE; i++) {
        // Scale chaotic values to match signal intensity range before XOR
        uint8_t scaledKey = static_cast<uint8_t>(fabs(chaoticSequence[i]) * 100) % 256;
        result[i] = static_cast<uint8_t>(transformedSignal[i]) ^ scaledKey;
    }
    return result;
}

// ---------------------------------------------------------------------------------
// Chaotic Permutation Based on Sign of x[0]
vector<uint8_t> chaoticPermutation(vector<uint8_t> data, const vector<double>& chaoticSequence) {
    if (chaoticSequence[0] > 0) {
        for (int i = 0; i < FRAME_SIZE - 1; i += 2) {
            swap(data[i], data[i + 1]);
        }
    } else {
        reverse(data.begin(), data.end());
    }
    return data;
}

// ---------------------------------------------------------------------------------
// Complete Encryption Function
vector<uint8_t> encryptSignal(const vector<int>& speechSignal) {
    // Apply Haar DWT (4-level)
    vector<int16_t> transformedSignal = haarDWT4(speechSignal);

    // Generate 16 chaotic values
    vector<double> chaoticSequence = generateChen4DSequence(FRAME_SIZE);

    // Apply XOR masking
    vector<uint8_t> maskedSignal = bitwiseXOR(transformedSignal, chaoticSequence);

    // Apply chaotic permutation
    vector<uint8_t> encryptedData = chaoticPermutation(maskedSignal, chaoticSequence);

    return encryptedData;
}
