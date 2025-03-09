#include "ap_fixed.h"
#include "hls_stream.h"

#define FRAME_SIZE 128  // 128 samples per frame
#define SAMPLE_RATE 16000  // Assuming 16kHz sampling rate
#define FRAME_DURATION_MS 10  // 10ms per frame
#define TOTAL_SAMPLES (SAMPLE_RATE * FRAME_DURATION_MS / 1000)  // Total samples per frame

typedef ap_fixed<32, 8> fixed_point;

// Ensure proper linkage
extern "C" void framing(hls::stream<fixed_point> &input_signal,
                               hls::stream<fixed_point> &output_frames) {
    #pragma HLS INTERFACE axis port=input_signal
    #pragma HLS INTERFACE axis port=output_frames
    #pragma HLS INTERFACE s_axilite port=return
    #pragma HLS PIPELINE

    static fixed_point buffer[FRAME_SIZE];  // Buffer to store one frame

    while (!input_signal.empty()) {
        for (int i = 0; i < FRAME_SIZE; i++) {
            buffer[i] = input_signal.read();  // Read 128 samples per frame
        }
        for (int i = 0; i < FRAME_SIZE; i++) {
            output_frames.write(buffer[i]);  // Send frame to output stream
        }
    }
}
