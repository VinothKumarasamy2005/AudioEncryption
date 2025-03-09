#ifndef ENCRYPTION_IP_H
#define ENCRYPTION_IP_H

// Ensure GMP doesn't cause redefinition issues
#ifndef __GMP_LIBGMP_DLL
#define __GMP_LIBGMP_DLL  0
#endif

#include <hls_math.h>
#include <ap_fixed.h>

// Define fixed-point type
typedef ap_fixed<32, 16> fixed32_t;

// Function prototype
extern "C" {
    void encryption_ip(fixed32_t input_data[128], fixed32_t output_data[128]);
}

#endif // ENCRYPTION_IP_H
