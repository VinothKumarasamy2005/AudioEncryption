#include "ap_fixed.h"
#include "hls_stream.h"
#include <iostream>
#include <fstream>

using namespace std;

#define FRAME_SIZE 128
#define SAMPLE_RATE 16000
#define TOTAL_SAMPLES 16000  // 1 second of speech data

typedef ap_fixed<32, 8> fixed_point;

// Function prototype
extern "C" void framing(hls::stream<fixed_point> &input_signal,
                               hls::stream<fixed_point> &output_frames);

int main() {
    hls::stream<fixed_point> input_signal;
    hls::stream<fixed_point> output_frames;

    // Corrected path formatting for Windows
    ifstream file("C:\\\\Users\\\\Mohamed Rinos\\\\Downloads\\\\longchirp-88445.wav", ios::binary);

    if (!file) {
        cerr << "Error: Cannot open speech file!" << endl;
        return -1;
    }

    fixed_point sample;
    int count = 0;

    // Read speech samples from file
    while (file.read(reinterpret_cast<char*>(&sample), sizeof(sample)) && count < TOTAL_SAMPLES) {
        input_signal.write(sample);
        count++;
    }
    file.close();

    // Run the framing function
    framing(input_signal, output_frames);

    // Print first few frames for verification
    cout << "\nFramed Speech Output (First Frame):\n";
    for (int i = 0; i < FRAME_SIZE; i++) {
        cout << output_frames.read() << " ";
    }
    cout << "\n";

    return 0;
}
