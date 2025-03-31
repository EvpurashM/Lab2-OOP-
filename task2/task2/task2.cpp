#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>

const int MAX_LENGTH = 128;

// Function to pad the string with spaces up to 128 characters
std::string padString(const std::string& input) {
    std::string result = input;
    result.resize(MAX_LENGTH, ' ');
    return result;
}

// Function to encrypt a character
uint16_t encryptChar(char ch, int position) {
    uint16_t encrypted = 0;
    encrypted |= (static_cast<uint16_t>(ch) & 0xFF) << 1; // ASCII code of the letter (8 bits) in bits 1-8
    encrypted |= (position & 0x7F) << 9; // Position of the letter (7 bits) in bits 9-15

    // Calculate parity
    int parity = std::bitset<15>(encrypted).count() % 2;
    encrypted |= parity; // Set the parity bit

    return encrypted;
}

// Function to encrypt and save to a file
void encryptAndSaveToFile(const std::string& text, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string paddedText = padString(text);
    for (size_t i = 0; i < paddedText.size(); ++i) {
        uint16_t encryptedChar = encryptChar(paddedText[i], i);
        file.write(reinterpret_cast<const char*>(&encryptedChar), sizeof(uint16_t));
    }

    file.close();
    std::cout << "Data successfully encrypted and saved to " << filename << std::endl;
}

// Function to decrypt a character
char decryptChar(uint16_t encrypted, int& position) {
    char ch = static_cast<char>((encrypted >> 1) & 0xFF);
    position = (encrypted >> 9) & 0x7F;
    return ch;
}

// Function to read the encrypted file and decrypt it
void decryptAndDisplay(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<char> decryptedText(MAX_LENGTH, ' ');
    for (size_t i = 0; i < MAX_LENGTH; ++i) {
        uint16_t encryptedChar;
        file.read(reinterpret_cast<char*>(&encryptedChar), sizeof(uint16_t));
        if (file.eof()) break;
        int position;
        char decryptedChar = decryptChar(encryptedChar, position);
        if (position < MAX_LENGTH) {
            decryptedText[position] = decryptedChar;
        }
    }

    file.close();

    std::string outputText(decryptedText.begin(), decryptedText.end());
    std::cout << "Decrypted text: " << outputText << std::endl;
}

int main() {
    std::string inputText;
    std::cout << "Enter text to encrypt (up to 128 characters): ";
    std::getline(std::cin, inputText);

    encryptAndSaveToFile(inputText, "encrypted.bin");

    std::cout << "\nDecrypting from file: " << std::endl;
    decryptAndDisplay("encrypted.bin");

    return 0;
}
