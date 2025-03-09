// ---------------------------------------------------------------------------------
// TESTBENCH
#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;
#define FRAME_SIZE 16

void encryfinal(const int speechSignal[FRAME_SIZE], double encryptedSignal[FRAME_SIZE]);
int main() {
    int speechSignal[FRAME_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160};
    double encryptedData[FRAME_SIZE];

    cout << "Original Speech Signal: ";
    for (int i = 0; i < FRAME_SIZE; i++) cout << speechSignal[i] << " ";
    cout << endl;

    // Encrypt the signal
    encryfinal(speechSignal, encryptedData);

    cout << "Encrypted Signal:\n";
    for (int i = 0; i < FRAME_SIZE; i++) cout << encryptedData[i] << " ";
    cout << "\n";

    return 0;
}
