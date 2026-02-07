#ifndef VAULT_H
#define VAULT_H

#include <string>

class Vault {
    public:
        static bool isEncrypted(const std::string& filename);
        static bool encryptFile(const std::string& inputfile, const std::string& outfile, const std::string_view password);
        static bool decryptFile(const std::string& inputfile, const std::string& outfile, const std::string_view password);
};
#endif