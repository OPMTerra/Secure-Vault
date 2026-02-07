# Secure Vault (C++ CLI) 🛡️

A high-performance, command-line file encryption tool built in C++.

Secure Vault handles file encryption at the **binary level**, allowing it to secure any file type (Images, Videos, PDFs, Executables) without corrupting data. It utilizes a **Stream-Based Architecture** to process multi-gigabyte files with constant O(1) memory usage.

## 🚀 Key Features

* **Binary Stream Processing:** Uses `std::ifstream` and `std::ofstream` in binary mode to handle raw byte data, preventing OS-level text formatting corruption.
* **Memory Safe:** Implements a fixed-size buffer (1MB) to process files of *any* size (even 100GB+) without causing RAM spikes or stack overflows.
* **XOR Stream Cipher:** Uses a rolling-key polyalphabetic substitution algorithm for fast, symmetric encryption.
* **File Integrity Checks:** Features a custom "Canary" verification system. The tool injects an encrypted signature into the file header to detect incorrect passwords immediately, preventing data corruption on failed decryption attempts.
* **Automatic Mode Detection:** Analyzes custom file headers (`VAULT_V1`) to automatically switch between Encryption and Decryption modes.

## 🛠️ Technical Implementation

This project demonstrates core Systems Programming concepts:

* **Buffer Management:** Chunk-based reading/writing for large datasets.
* **Bitwise Operations:** Low-level memory manipulation using XOR logic.
* **Modular Architecture:** Separation of concerns (Interface vs. Implementation) using Header (`.h`) and Source (`.cpp`) files.
* **Error Handling:** Robust checks for file streams, permissions, and integrity validation.

## 📦 Installation & Build

You need a C++ compiler (GCC/G++ recommended).

**1. Clone the repository**
```bash
git clone [https://github.com/OPMTerra/Secure-Vault.git](https://github.com/OPMTerra/Secure-Vault.git)
cd Secure-Vault
```

**2. Compile the source**
```bash
g++ main.cpp Vault.cpp -o vault
```

## 💻 Usage

**1. Ecrypting a file** Simply provide the filename. Secure Vault automatically detects it is a raw file.
```bash
./vault my_secret.pdf
> [RAW] Detected unencrypted file.
> [INPUT] Set a password: ****
> [SUCCESS] Encrypted file created: my_secret.pdf.vault
```

**2. Decrypting a File** Provide the .vault file. The tool validates the header and password before unlocking.
```bash
./vault my_secret.pdf.vault
> [LOCKED] Detected encrypted file.
> [INPUT] Enter the password: ****
> [INFO] Processing... 100%
> [SUCCESS] Restored to my_secret.pdf
```

## 🛡️ License
This project is open-source and available under the MIT License.