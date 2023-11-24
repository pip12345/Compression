#include "huff.h"

#include <unordered_map>
#include <algorithm>

namespace huff {

    Tree::Tree() {

    }

    void Tree::min_heap_add(Node n) {
        min_heap.push(new Node(n.data, n.freq));
    }

    bool Tree::cmp_map_sort(std::pair<char, int> &a, std::pair<char, int> &b) {
        return a.second < b.second;
    }

    std::vector<Node> Tree::string_to_nodes(std::string str) {

        /// Count the frequency of each character, unsorted

        std::unordered_map<char, int> freq_map; // holds a map of each character and its frequency
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

        /// Sort by value

        // Copy unsorted map into vector
        for (auto& it : freq_map) {
            freq_sorted.push_back(it);
        }

        // Sort
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

    void Tree::add(std::stringstream buffer) {
        add(buffer.str());
    }


}