#ifndef COMPRESSION_HUFF_H
#define COMPRESSION_HUFF_H

#include <iostream>
#include <sstream>
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
        explicit Tree(const std::stringstream& buffer); // Build a tree out of the passed stringstream
        explicit Tree(const std::string& string); // Build a tree out of the passed string
        Tree(); // Empty tree

        void add(const std::string& str); // Add a string to the tree
        void add(const std::stringstream& buffer); // Add the contents of an entire buffer to the tree

        void print_tree(); // Print tree



    private:

        // Hold pointers to the current node's root, left and right node, used for building/navigating the tree
        Node *root{}, *left{}, *right{};

        // Min priority queue (min heap) used for building and storing the Huffman tree
        std::priority_queue<Node*, std::vector<Node*>, Node_compare> min_heap;

        std::vector<Node> string_to_nodes(std::string str); // Returns a frequency-sorted vector of a pair of each character and its frequency

        void min_heap_add(const Node& n);
        void min_heap_add(const std::vector<Node>& n);
        void build_tree();
        void print_from_node(Node* n, std::string huff_code); // Recursively used to print all child nodes starting from node n

        static bool cmp_map_sort(std::pair<char, int>& a, std::pair<char, int>& b);

    };

    class Huffman_coder {
    public:
        std::string encode(); // Encode and return the encoded string
        std::string return_freq_table(); // Returns the freq_table as a string which is required for decoding

        void add_freq_table(std::string); // Adds freq_table to tree
        void decode(std::string); // decodes passed string using current freq_table

    private:
        Tree tree();
    };

}

#endif // HUFF_H