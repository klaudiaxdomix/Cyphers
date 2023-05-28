#include <iostream>
#include <string>

class Cipher {
public:
    virtual std::string encrypt(const std::string& message) const = 0;
    virtual std::string decrypt(const std::string& encryptedMessage) const = 0;
};

class CaesarCipher : public Cipher {
private:
    int key;

public:
    CaesarCipher(int key) {
        this->key = key;
    }

    std::string encrypt(const std::string& message) const override {
        std::string encryptedMessage = message;

        for (char& character : encryptedMessage) {
            if (isalpha(character)) {
                if (isupper(character))
                    character = (character - 'A' + key) % 26 + 'A';
                else
                    character = (character - 'a' + key) % 26 + 'a';
            }
        }

        return encryptedMessage;
    }

    std::string decrypt(const std::string& encryptedMessage) const override {
        std::string decryptedMessage = encryptedMessage;

        for (char& character : decryptedMessage) {
            if (isalpha(character)) {
                if (isupper(character))
                    character = (character - 'A' - key + 26) % 26 + 'A';
                else
                    character = (character - 'a' - key + 26) % 26 + 'a';
            }
        }

        return decryptedMessage;
    }
};

class AtbashCipher : public Cipher {
public:
    std::string encrypt(const std::string& message) const override {
        std::string encryptedMessage = message;

        for (char& character : encryptedMessage) {
            if (isalpha(character)) {
                if (isupper(character))
                    character = 'Z' - (character - 'A');
                else
                    character = 'z' - (character - 'a');
            }
        }

        return encryptedMessage;
    }

    std::string decrypt(const std::string& encryptedMessage) const override {
        return encrypt(encryptedMessage);  // Decrypting with Atbash is the same as encrypting
    }
};

int main() {
    int caesarKey, atbashKey;
    std::string message;

    std::cout << "Enter the Caesar Cipher key: ";
    std::cin >> caesarKey;
    std::cout << "Enter the Atbash Cipher key (not used): ";
    std::cin >> atbashKey;
    std::cin.ignore();

    CaesarCipher caesarCipher(caesarKey);
    AtbashCipher atbashCipher;

    std::cout << "Enter a message to encrypt: ";
    std::getline(std::cin, message);

    std::string caesarEncrypted = caesarCipher.encrypt(message);
    std::string caesarDecrypted = caesarCipher.decrypt(caesarEncrypted);

    std::string atbashEncrypted = atbashCipher.encrypt(message);
    std::string atbashDecrypted = atbashCipher.decrypt(atbashEncrypted);

    std::cout << "\n--- Results ---\n";
    std::cout << "Caesar Cipher:\n";
    std::cout << "Encrypted Message: " << caesarEncrypted << '\n';
    std::cout << "Decrypted Message: " << caesarDecrypted << '\n';

    std::cout << "\nAtbash Cipher:\n";
    std::cout << "Encrypted Message: " << atbashEncrypted << '\n';
    std::cout << "Decrypted Message: " << atbashDecrypted << '\n';

    return 0;
}
