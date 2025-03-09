#include "chen_hyperchaos.h"
#include <iostream>

int main() {
    const int N = 10000;  // Number of iterations
    float x[N], y[N], z[N], w[N];

    // Parameters from your problem
    float dt = 0.001;
    float alpha = 36, sigma = 16, beta = 3, gamma = 28, epsilon = 0.2;

    // Run the hyperchaotic system
    chen_hyperchaos(dt, N, alpha, sigma, beta, gamma, epsilon, x, y, z, w);

    // Print first 10 values (compare with image.png)
    for (int i = 0; i < 10; i++) {
        std::cout << "Iteration " << i << ": x=" << x[i] << ", y=" << y[i]
                  << ", z=" << z[i] << ", w=" << w[i] << std::endl;
    }

    return 0;
}
