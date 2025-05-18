#include <chrono>
#include <iostream>
#include <memory>

struct Node {
    int data;
    using node_ptr = std::shared_ptr<Node>;
    node_ptr next;
    Node(int val) : data(val), next(nullptr) {};

    static void run() {
        const size_t TOTAL = 10000;
        node_ptr head = std::make_shared<Node>(0);
        node_ptr current = head;
        for (size_t i = 1; i < TOTAL; ++i) {
            current->next = std::make_shared<Node>(i);
            current = current->next;
        }
        std::cout << "done" << std::endl;
    }

    //~Node() { std::cout << data << std::endl; }
};

int main() { Node::run(); }

// struct Node {
//     int data;
//     using node_ptr = Node *;
//     node_ptr next;
//     Node(int val) : data(val), next(nullptr) {};

//     static void run() {
//         const size_t TOTAL = 1'500'000;
//         node_ptr head = new Node(0);
//         node_ptr current = head;
//         for (size_t i = 1; i < TOTAL; ++i) {
//             current->next = new Node(i % 100);
//             current = current->next;
//         }
//         std::cout << "done" << '\n';
//     }
// };
