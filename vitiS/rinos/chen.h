#ifndef CHEN_HYPERCHAOS_H_
#define CHEN_HYPERCHAOS_H_

void chensy(
    float dt,
    int num_iterations,
    float alpha, float sigma, float beta, float gamma, float epsilon,
    float *x_out, float *y_out, float *z_out, float *w_out
);

#endif
