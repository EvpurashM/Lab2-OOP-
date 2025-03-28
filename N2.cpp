#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

// Function to compute the parity bit (even number of 1s -> 0, odd -> 1)
int parity_bit(int value) {
    return __builtin_parity(value);  // Built-in function for parity calculation
}

void encrypt_text(const string& input_text) {
    ofstream output("encoded.bin", ios::binary);
    
    if (!output) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    string text = input_text;
    while (text.length() < 128) text += ' '; // Pad to 128 characters

    for (size_t i = 0; i < 128; i++) {
        unsigned short encoded_char = 0;  // 16-bit number
        encoded_char |= (text[i] & 0xFF) << 1; // Store ASCII code (bits 1-8)
        encoded_char |= (i & 0x7F) << 9;  // Store position (bits 9-15)
        encoded_char |= parity_bit(encoded_char); // Add parity bit (bit 0)

        output.write(reinterpret_cast<const char*>(&encoded_char), sizeof(encoded_char));
    }

    output.close();
    cout << "Encryption completed. Data saved in encoded.bin" << endl;
}

int main() {
    ifstream input("input.txt");
    string text;

    if (input) {
        getline(input, text);
        input.close();
    } else {
        cout << "Enter text (max 128 characters): ";
        getline(cin, text);
    }

    encrypt_text(text);
    return 0;
}
