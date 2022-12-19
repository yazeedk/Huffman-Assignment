#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

Node* buildHuffmanTree(unordered_map<char, int>& frequency_table) {
    priority_queue<Node*, vector<Node*>, Compare> priority_queue;
    for (auto& pair : frequency_table) {
        priority_queue.push(new Node(pair.first, pair.second));
    }

    while (priority_queue.size() > 1) {
        Node* left_child = priority_queue.top();
        priority_queue.pop();
        Node* right_child = priority_queue.top();
        priority_queue.pop();
        Node* parent = new Node('\0', left_child->frequency + right_child->frequency);
        parent->left = left_child;
        parent->right = right_child;
        priority_queue.push(parent);
    }

    return priority_queue.top();
}

void createHuffmanCode(Node* root, string code, unordered_map<char, string>& huffman_code) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        huffman_code[root->data] = code;
    }

    createHuffmanCode(root->left, code + "0", huffman_code);
    createHuffmanCode(root->right, code + "1", huffman_code);
}

string huffmanEncoding(const string& data, unordered_map<char, string>& huffman_code) {
    string encoded_data;
    for (char c : data) {
        encoded_data += huffman_code[c];
    }
    return encoded_data;
}

string huffmanDecoding(Node* root, const string& encoded_data) {
    string decoded_data;
    Node* current = root;
    for (char c : encoded_data) {
        if (c == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->data != '\0') {
            decoded_data += current->data;
            current = root;
        }
    }
    return decoded_data;
}