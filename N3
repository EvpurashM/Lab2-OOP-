#include <iostream>
#include <fstream>

using namespace std;

void decrypt_text() {
    ifstream input("encoded.bin", ios::binary);
    ofstream output("output.txt");

    if (!input || !output) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string decrypted_text(128, ' '); // Prepare a 128-character string

    for (size_t i = 0; i < 128; i++) {
        unsigned short encoded_char;
        input.read(reinterpret_cast<char*>(&encoded_char), sizeof(encoded_char));

        char character = (encoded_char >> 1) & 0xFF; // Extract ASCII code
        size_t position = (encoded_char >> 9) & 0x7F; // Extract position

        decrypted_text[position] = character; // Restore character at the correct position
    }

    cout << "Decrypted text: " << decrypted_text << endl;
    output << decrypted_text << endl;

    input.close();
    output.close();
}

int main() {
    decrypt_text();
    return 0;
}
