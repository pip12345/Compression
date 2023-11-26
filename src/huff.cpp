#include "huff.h"
#include <algorithm>

namespace huff {

    bool Huffman_coder::cmp_map_sort(std::pair<char, int> &a, std::pair<char, int> &b) {
        return a.second < b.second;
    }

    void Tree::add_freq_table(const std::vector<Node> &n) {
        // Wipe current contents of min heap (tree)
        clear_min_heap();

        // Add new freq_table to min_heap
        for (auto i: n) {
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

    void Tree::print_from_node(Node *n, std::string code_recursive) {

        // If null, we've reached the end, break from recursion
        if (n == nullptr) {
            return;
        }

        // Only print if it's not a root node
        if (n->data != '~') {
            std::cout << n->data << ": " << code_recursive << "\n";
        }

        print_from_node(n->left, code_recursive + "0"); // Left child, add a 0 to the code
        print_from_node(n->right, code_recursive + "1"); // Right child, add 1 to the code
    }

    void Tree::coding_table_from_node(Node *n, std::string code_recursive, std::map<char, std::string> &coding_table) {
        // If null, we've reached the end, break from recursion
        if (n == nullptr) {
            return;
        }

        // Only output if it's not a root node
        if (n->data != '~') {
            coding_table.insert(std::make_pair(n->data, code_recursive));
        }

        coding_table_from_node(n->left, code_recursive + "0", coding_table); // Left child, add a 0 to the code
        coding_table_from_node(n->right, code_recursive + "1", coding_table); // Right child, add 1 to the code
    }

    void Tree::print_debug_tree() {
        print_from_node(root, "");
    }

    std::map<char, std::string> Tree::return_coding_table() {
        std::map<char, std::string> temp_coding_table{};
        coding_table_from_node(root, "", temp_coding_table);

        return temp_coding_table;
    }

    void Tree::clear_min_heap() {
        while(!min_heap.empty()) {
            min_heap.pop();
        }
    }

    std::vector<Node> Huffman_coder::string_to_nodes(const std::string &text_str) {
        /// Count the frequency of each character, output map is sorted alphabetically first

        std::map<char, int> freq_map; // holds a map of each character and its frequency, sorted alphabetically
        std::vector<std::pair<char, int>> freq_sorted{}; // Sorted by-frequency vector of the map
        std::vector<Node> nodes{};

        // Traverse the string
        for (int i{0}; text_str[i]; i++) {
            // If the current character hasn't been found before, set frequency to 1
            if (freq_map.find(text_str[i]) == freq_map.end()) {
                freq_map.insert(std::make_pair(text_str[i], 1));
            } else {
                // If the character already exists in the map, increase the frequency
                freq_map[text_str[i]]++;
            }
        }

        //        for (auto& it : freq_map) {
        //            std::cout << it.first << ' ' << it.second << '\n';
        //        }

        /// Now re-sort by frequency

        // Copy map into vector
        for (auto &it: freq_map) {
            freq_sorted.push_back(it);
        }

        // Sort by frequency
        std::sort(freq_sorted.begin(), freq_sorted.end(), cmp_map_sort);

        //        for (auto& it : freq_sorted) {
        //            std::cout << it.first << ' ' << it.second << '\n';
        //        }

        /// Convert sorted vector to nodes and add them to nodes vector
        for (auto &it: freq_sorted) {
            Node temp(it.first, it.second);
            nodes.push_back(temp);
        }

        return nodes;
    }

    std::string Huffman_coder::code_with_coding_table(const std::string &text_str,
                                                      const std::map<char, std::string> &coding_table) {

        auto temp = coding_table.find('P');
        std::string coded{};

        for (auto i: text_str) {
            coded.append(coding_table.find(i)->second);
        }

        return coded;
    }

    std::string Huffman_coder::decode_with_coding_table(std::string encoded_text_str,
                                                        const std::map<char, std::string> &coding_table) {

        std::string read_buffer{};
        std::string output_string{};
        auto reversed_table = reverse_map(coding_table);

        // We will copy an element from encoded_text_str to read_buffer, then remove it from the encoded_text_str
        // Read_buffer will be checked to the coding table:
        // If the contents of read_buffer are equal to the code of a character from the coding table,
        // then the corrresponding character will be added to the output string and read_buffer will be wiped
        // This will continue until encoded_text_str is empty;

        // add a code number to the buffer until it is something that exists inside the coding table
        while (!encoded_text_str.empty()) {
            read_buffer.push_back(encoded_text_str.front()); // Add front element of encoded text to read buffer

            encoded_text_str.erase(encoded_text_str.begin()); // delete front element from encoded text

            // Check if the code contents of read buffer correspond to a character in the map
            // map.find() returns the end iterator if nothing is found

            // If the value exists
            auto temp = reversed_table.find("010");

            if (reversed_table.find(read_buffer) != reversed_table.end()) {

                /// THIS DOESNT WORK YET

                // add the corresponding character of the code to the output string
                output_string.push_back(reversed_table.find(read_buffer)->second);

                // Wipe the read_buffer
                read_buffer.clear();
            }

            std::cout << "read buffer:      " << read_buffer << std::endl;
            std::cout << "encoded_text_str: " << encoded_text_str << std::endl;
            std::cout << "output_string:    " << output_string << std::endl;


        }

        if (!read_buffer.empty()) {
            std::cerr << "read_buffer wasn't empty, therefore a character was in the decoding string that wasn't encoded in the coding table!";
        }

        return output_string;
    }

    std::string Huffman_coder::encode(const std::string &text_str) {
        auto freq_table = string_to_nodes(text_str);
        tree.add_freq_table(freq_table);
        auto coding_table = tree.return_coding_table();
        tree.print_debug_tree();

        // Encode message with coding table
        auto coded_message = code_with_coding_table(text_str, coding_table);

        // Return encoded message
        return coded_message;
    }

    std::string Huffman_coder::decode(const std::string &encoded_text_str, const std::string &freq_table_str) {

        auto freq_table = string_to_nodes("Programming"); /// TO DO ADD THIS, FREQ_TABLE_STR TO FREQ_TABLE INSTEAD OF STRING_TO_NODES
        tree.add_freq_table(freq_table);
        auto coding_table = tree.return_coding_table();
        tree.print_debug_tree();

        // Decode message with coding table
        auto decoded_message = decode_with_coding_table(encoded_text_str, coding_table);

        // Return encoded message
        return decoded_message;
    }


}