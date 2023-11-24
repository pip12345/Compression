#include "huff.h"

#include <unordered_map>
#include <map>

namespace huff {

    Tree::Tree() {

    }

    void Tree::min_heap_add(Node n) {
        min_heap.push(new Node(n.data, n.freq));
    }

    std::vector<Node> Tree::string_to_node(std::string str) {

        /// Count the frequency of each character

        std::unordered_map<char, int> freq_map; // holds a map of each character and its frequency

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

        for (auto& it : freq_map) {
            std::cout << it.first << ' ' << it.second << '\n';
        }




    }


}