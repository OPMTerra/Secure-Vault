#include <iostream>
#include <string>
#include "Vault.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1; 
    }

    std::string filename = argv[1];
    std::string password;
    std:: string outfilename;
    if (Vault::isEncrypted(filename)) {
        std::cout << "[LOCKED] Detected encrypted file." << std::endl;
        std::cout << "[INPUT] Enter the password: ";
        std::cin >> password;

        if (filename.length() >= 6 && filename.substr(filename.length() - 6) == ".vault")
            outfilename = filename.substr(0, filename.length() - 6);
        else
            outfilename = filename + ".dec";
        if (Vault::decryptFile(filename, outfilename, password)) {
            std::cout << "[SUCCESS] Restored to " << outfilename << std::endl;
            return 0;
        }
        else {
            std::cerr << "[ERROR] Decryption failed. Incorrect password or corrupted file." << std::endl;
            return 1;
        }
    }
    else  {
        std::cout << "[RAW] Detected unecrypted file." << std::endl;
        std::cout << "[INPUT]Set a password: ";
        std::cin >> password;
        outfilename = filename + ".vault";
        if(Vault::encryptFile(filename, outfilename, password)){
        std::cout << "[SUCCESS] Encrypted file created " << outfilename << std::endl;
        }
        else {
            std::cerr << "[ERROR] Encryption failed. Check file permissions and try again." << std::endl;
            return 1;
        }
    }
    return 0;
}