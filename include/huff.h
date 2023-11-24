#ifndef COMPRESSION_HUFF_H
#define COMPRESSION_HUFF_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace huff {

    // Min heap node in the huffman tree
    struct Node {
        int freq;
        char data;
        Node *left{nullptr};
        Node *right{nullptr};

        Node(char data, int freq) {
            this->freq = freq;
            this->data = data;
        }
    };

    // Comparison object to be used to order the priority queue
    // This struct is passed to std::priority_queue to change the ordering
    struct Node_compare {
        bool operator()(Node *l, Node *r) {
            // highest priority item has lowest frequency
            return l->freq > r->freq;
        }
    };

    class Tree {
    public:
        Tree(std::stringstream buffer); // Build a tree out of the passed stringstream
        Tree(std::string string); // Build a tree out of the passed string
        Tree(); // Empty tree

        void add(char data, int freq); // Add a character with a certain frequency to the tree
        void add(std::string str); // Add a string to the tree
        void add(std::stringstream buffer); // Add the contents of an entire buffer to the tree

        std::vector<Node> string_to_node(std::string str);

    private:
        // Hold pointers to the current node's root, left and right node, used for building/navigating the tree
        Node *root, *left, *right;

        // Min priority queue (min heap) used for building the Huffman tree
        std::priority_queue<Node*, std::vector<Node*>, Node_compare> min_heap;

        void min_heap_add(Node n);

//        void min_heap_fill(std::string str);
//        void min_heap_fill(std::stringstream  buffer);



        //std::vector<Node> pool;
        //std::unordered_map<char, std::vector<bool>> huffmanCode;

        // traverse the Huffman Tree and store Huffman Codes in a map.
        //void fillmap(Node *node, const std::vector<bool> &str);

        // Builds Huffman Tree and decode given input text
        //void buildHuffmanTree(const std::string &text);

        //std::vector<bool> encode(const std::string &text);

        // traverse the Huffman Tree and decode the encoded string
        //std::string decode(const std::vector<bool> &encoded);

    };


}

#endif // HUFF_H