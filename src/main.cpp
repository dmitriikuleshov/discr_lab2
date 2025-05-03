#include <rb_tree.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace cust;

struct KeyValuePair {
    std::string key;
    uint64_t value;

    void serialize(std::ostream &os) const {
        uint64_t len = key.size();
        os.write(reinterpret_cast<const char *>(&len), sizeof(len));
        os.write(key.data(), len);
        os.write(reinterpret_cast<const char *>(&value), sizeof(value));
    }

    static KeyValuePair deserialize(std::istream &is) {
        KeyValuePair v;
        uint64_t len;
        is.read(reinterpret_cast<char *>(&len), sizeof(len));
        std::vector<char> buffer(len);
        is.read(buffer.data(), len);
        v.key.assign(buffer.data(), len);
        is.read(reinterpret_cast<char *>(&v.value), sizeof(v.value));
        return v;
    }
};

bool operator==(KeyValuePair const &a, KeyValuePair const &b) {
    return a.key == b.key;
}

bool operator<(KeyValuePair const &a, KeyValuePair const &b) {
    return a.key < b.key;
}

void lower(std::string &s) {
    for (auto &c : s) {
        if ('A' <= c && c <= 'Z') {
            c += 'a' - 'A';
        }
    }
}

std::istream &operator>>(std::istream &iss, KeyValuePair &v) {
    iss >> v.key >> v.value;
    lower(v.key);
    return iss;
}

std::ostream &operator<<(std::ostream &os, KeyValuePair &v) {
    return os << v.key << " " << v.value;
}

int main() {
    RBTree<KeyValuePair> tree;

    std::string word;
    while (std::cin >> word) {
        if (word == "+") {
            KeyValuePair v;
            std::cin >> v;
            try {
                tree.add(v);
                std::cout << "OK\n";
            } catch (...) {
                std::cout << "Exist\n";
            }
        } else if (word == "-") {
            std::cin >> word;
            lower(word);
            KeyValuePair v{word, 0};
            try {
                tree.remove(v);
                std::cout << "OK\n";
            } catch (...) {
                std::cout << "NoSuchWord\n";
            }
        } else if (word == "!") {
            std::string cmd, filename;
            std::cin >> cmd;
            std::cin.get(); // Пропустить пробел
            std::getline(std::cin, filename);
            if (cmd == "Save") {
                std::ofstream off(filename, std::ios::binary);
                tree.saveToBinary(off);
                off.close();
                std::cout << "OK\n";
            } else if (cmd == "Load") {
                if (!std::filesystem::exists(filename)) {
                    std::cout << "Error: File '" << filename
                              << "' does not exist\n";
                } else {
                    std::ifstream iff(filename, std::ios::binary);
                    if (iff) {
                        tree = RBTree<KeyValuePair>::readFromBinary(iff);
                        std::cout << "OK\n";
                    } else {
                        std::cout << "Error: Cannot open file\n";
                    }
                    iff.close();
                }
            }

        } else if (word == "print") {
            tree.printTree(std::cout);
            std::cout << "\n";
        } else {
            try {
                lower(word);
                auto v = tree.find(KeyValuePair{word, 0});
                std::cout << "OK: " << v->value << "\n";
            } catch (...) {
                std::cout << "NoSuchWord\n";
            }
        }
    }

    return 0;
}