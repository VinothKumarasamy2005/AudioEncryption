#include <iostream>
#include <vector>

using namespace std;

// Function Prototype
vector<uint8_t> encryptSignal(const vector<int>& speechSignal);

int main() {
    // Define a test speech signal (16 elements)
    vector<int> speechSignal = {200, 233, 252, 209, 211, 59, 231, 173,
                                172, 166, 4, 122, 24, 40, 104, 202};

    // Print the original speech signal
    cout << "Original Speech Signal: ";
    for (int val : speechSignal) cout << val << " ";
    cout << endl;

    // Encrypt the signal
    vector<uint8_t> encryptedData = encryptSignal(speechSignal);

    // Display encrypted output
    cout << "Encrypted Data: ";
    for (int val : encryptedData) cout << static_cast<int>(val) << " ";
    cout << endl;

    return 0;
}
