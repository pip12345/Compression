#include "huff.h"

#include <map>
#include <algorithm>

namespace huff {

    Tree::Tree() {}

    Tree::Tree(const std::stringstream &buffer) {
        add(buffer);
    }

    Tree::Tree(const std::string &string) {
        add(string);
    }

    bool Tree::cmp_map_sort(std::pair<char, int> &a, std::pair<char, int> &b) {
        return a.second < b.second;
    }

    std::vector<Node> Tree::string_to_nodes(std::string str) {

        /// Count the frequency of each character, output map is sorted alphabetically first

        std::map<char, int> freq_map; // holds a map of each character and its frequency, sorted alphabetically
        std::vector<std::pair<char, int>> freq_sorted{}; // Sorted by-value vector of the map
        std::vector<Node> nodes{};

        // Traverse the string
        for(int i{0}; str[i]; i++) {
            // If the current character hasn't been found before, set frequency to 1
            if (freq_map.find(str[i]) == freq_map.end()) {
                freq_map.insert(std::make_pair(str[i], 1));
            } else {
                // If the character already exists in the map, increase the frequency
                freq_map[str[i]]++;
            }
        }

//        for (auto& it : freq_map) {
//            std::cout << it.first << ' ' << it.second << '\n';
//        }

        /// Now re-sort by frequency

        // Copy map into vector
        for (auto& it : freq_map) {
            freq_sorted.push_back(it);
        }

        // Sort by frequency
        std::sort(freq_sorted.begin(), freq_sorted.end(), cmp_map_sort);

//        for (auto& it : freq_sorted) {
//            std::cout << it.first << ' ' << it.second << '\n';
//        }

        /// Convert sorted vector to nodes and add them to nodes vector
        for (auto& it : freq_sorted) {
            Node temp(it.first, it.second);
            nodes.push_back(temp);
        }

        return nodes;

    }

    void Tree::add(const std::string& str) {
        auto nodes = string_to_nodes(str);
        min_heap_add(nodes);
    }

    void Tree::add(const std::stringstream& buffer) {
        add(buffer.str());
    }

    void Tree::min_heap_add(const Node& n) {
        min_heap.push(new Node(n.data, n.freq));
        build_tree();
    }

    void Tree::min_heap_add(const std::vector<Node>& n) {
        for (auto i : n) {
            min_heap.push(new Node(i.data, i.freq));
        }
        build_tree();
    }

    void Tree::build_tree() {
        // Iterate while heap has elements
        while (min_heap.size() > 1) {
            // Extract the 2 lowest freq items from heap
            left = min_heap.top();
            min_heap.pop();

            right = min_heap.top();
            min_heap.pop();

            // Add a new root node to these two nodes with the frequency being the sum of the frequency of both left and right children
            // '~' character reserved for indicating the root node
            root = new Node('~', left->freq + right->freq);
            root->left = left;
            root->right = right;

            // Push new tree part back into the min heap
            min_heap.push(root);
        }
    }

    void Tree::print_from_node(Node *n, std::string huff_code) {

        // If null, we've reached the end, break from recursion
        if (n == nullptr) {
            return;
        }

        // Skip the root nodes
        if (n->data != '~') {
            std::cout << n->data << ": " << huff_code << "\n";
        }

        print_from_node(n->left, huff_code + "0"); // Left child, add a 0 to the code
        print_from_node(n->right, huff_code + "1"); // Right child, add 1 to the code


    }

    void Tree::print_tree() {
        print_from_node(root, "");
    }
}