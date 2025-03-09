#include "chen.h"

void chensy(
    float dt,
    int num_iterations,
    float alpha, float sigma, float beta, float gamma, float epsilon,
    float *x_out, float *y_out, float *z_out, float *w_out
) {
    // Initial conditions
    float x = 0.0, y = 0.01, z = 0.01, w = 0.0;

    for (int i = 0; i < num_iterations; i++) {
        #pragma HLS PIPELINE II=1  // Optimize for speed
        float dx = alpha * (y - x);
        float dy = sigma * x - x * z + gamma * y - w;
        float dz = x * y - beta * z;
        float dw = x - epsilon;

        x += dt * dx;
        y += dt * dy;
        z += dt * dz;
        w += dt * dw;

        // Store outputs in arrays
        x_out[i] = x;
        y_out[i] = y;
        z_out[i] = z;
        w_out[i] = w;
    }
}
