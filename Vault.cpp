#include "Vault.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

const std::string HEADER = "VAULT_V1";
std::string Canary = "My Favorite food is Khichdi.";
const size_t buffer_size = 1024 * 1024;

bool Vault::isEncrypted(const std::string& filename){
    std::ifstream file2(filename, std::ios::binary);
    if (file2.is_open()) {
        char Headerbuffer[8];

        file2.read(Headerbuffer, 8);
        std::string Header(Headerbuffer, 8);
        if (Header == HEADER) return true;
        else return false;
    }
    else {
        std::cerr << "Error: Could not open the file." << std::endl;
        return false;
    }
}

bool Vault::encryptFile(const std::string& inputfile, const std::string& outfile, const std::string_view password) {
    std::ifstream infile(inputfile.data(), std::ios::binary);
    std::ofstream oufile(outfile.data(), std::ios::binary);

    if(!infile || !oufile) return false;

    size_t global_count = 0;
    
    int key_length = password.length();
    std::vector<char> Buffer(buffer_size);

    for (char c : HEADER) oufile.put(c);

    for (int i = 0; i < Canary.length(); ++i) {
        char ch = Canary[i] ^ password[i % key_length];
        oufile.put(ch);
    }
    global_count = Canary.length();
    long long total_size = std::filesystem::file_size(inputfile);
    long long current_read = 0;

    while (infile) {
        infile.read(Buffer.data(), buffer_size);
        size_t count = infile.gcount();
        

        if (count == 0) break;
        current_read += count;
        int percent = (current_read * 100) / total_size;
        if (percent % 5 == 0) {
            std::cout << "\r[INFO] Processing... " << percent << "%" <<std::flush;
        }
        for (int i = 0; i < count; ++i) {
            Buffer[i] ^= password[global_count % key_length];
            global_count++;
        }
        oufile.write(Buffer.data(), count);
    }
    std::cout << "\r[INFO] Processing... 100%" << std::endl;
    infile.close();
    oufile.close();
    return true;
}

bool Vault::decryptFile(const std::string& inputfile, const std::string& outfile, const std::string_view password) {
    std::ifstream infile(inputfile.data(), std::ios::binary);
    std::ofstream oufile(outfile.data(), std::ios::binary);

    if (!infile || !oufile) return false;
    
    int key_length = password.length();
    size_t global_count = 0;
    std::vector<char> Buffer(buffer_size);
    //skip the header
    infile.seekg(8, std::ios::beg);

    std::vector<char> canary_buffer(Canary.length());
    infile.read(canary_buffer.data(), Canary.length());
    std::string Canary_check = "";
    
    for (int i = 0; i < Canary.length(); ++i) {
        char ch = canary_buffer[i] ^ password[i % key_length];
        Canary_check += ch;
    }

    if (Canary_check != Canary) {
        //cleanup
        infile.close();
        oufile.close();
        //remove the output file if created
        std::filesystem::remove(outfile.data());
        return false;
    }
    global_count = Canary.length();
    long long total_size = std::filesystem::file_size(inputfile);
    long long current_read = 0;

    while (infile) {
        infile.read(Buffer.data(), buffer_size);
        size_t count = infile.gcount();

        if (count == 0) break;
        current_read += count;
        int percent = (current_read * 100) / total_size;
        if (percent % 5 == 0) {
            std::cout << "\r[INFO] Processing... " << percent << "%" << std::flush;
        }

        for (int i = 0; i < count; ++i) {
            Buffer[i] ^= password[global_count % key_length];
            global_count++;
        }
        oufile.write(Buffer.data(), count);
    }
    std::cout << "\r[INFO] Processing... 100%" << std::endl;
    infile.close();
    oufile.close();
    return true;
}