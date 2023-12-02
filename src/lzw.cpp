
#include "lzw.h"
#include <map>
#include <bitset>
#include <iostream>
#include <complex>

namespace lzw {
    std::string Lzw_coder::encode(const std::string &text_str) {
        std::map<std::string, int> dict{};
        int dict_size = 256;
        std::string coded_msg{};
        std::string first_input{}; // String because we need to be able to append characters: 't' + 'h' = "th"

        // Build default dictionary
        for (int i{0}; i < dict_size; i++) {
            dict[std::string{(char) i}] = i;
        }

        // Encode the text_str
        for (int i{0}; i < text_str.length(); i++) {
            char next_input = text_str[i];

            if (dict_size <= pow(2, CODED_MSG_BITS)) {
                // If first_input + next_input is in the dictionary
                if (dict.count(first_input + next_input)) {
                    first_input += next_input;
                } else {
                    // Output code
                    coded_msg.append(int_to_binary_str(dict[first_input]));
                    //std::cout << "-: " << dict[first_input] << "\n";

                    // Add first_input + next_input to the dictionary by setting new fake "ascii" value
                    dict[first_input + next_input] = dict_size++;
                    first_input = next_input;
                }
            } else {
                // If the dictionary is full, stop filling it and encode the rest of the file using the current dictionary
                /// Uncommenting the below breaks everything so badly even the debugger breaks
                /// So, instead of continuing encoding with the current dictionary if it's full, we're just going to give up and quit.
                //coded_msg.append(int_to_binary_str(dict["a"]));
                //coded_msg.append(int_to_binary_str(dict[std::string{text_str[i]}]));
                std::cerr << "\nDictionary Overflow, increase CODED_MSG_BITS!";
            }

        }

        // Print the last character
        if (!first_input.empty()) {
            coded_msg.append(int_to_binary_str(dict[first_input]));
        }

        return coded_msg;
    }

    std::string Lzw_coder::decode(const std::string &encoded_text_str) {
        std::map<int, std::string> dict{};
        std::string first_input{};
        std::string decoded_msg{};
        std::string temp{};

        int dict_size = 256;

        // Convert binary string to lzw index where each int is the char value of the dictionary
        auto lzw_indexes = binary_string_to_lzw_indexes(encoded_text_str);

        // Build default dictionary
        for (int i{0}; i < dict_size; i++) {
            dict[i] = (char) i;
        }

        // Set initial conditions (first character is always known)
        first_input = dict[lzw_indexes[0]];
        decoded_msg = dict[lzw_indexes[0]];

        // Continue on and decode from the 2nd
        for (int i{1}; i < lzw_indexes.size(); i++) {
            int next_input = lzw_indexes[i];

            if (dict.count(next_input)) {
                temp = dict[next_input];
            } else {
                temp = first_input + first_input[0];
            }

            decoded_msg += temp;
            dict[dict_size++] = first_input + temp[0];
            first_input = temp;
        }

        return decoded_msg;
    }

    std::string Lzw_coder::int_to_binary_str(const int &value) {
        int ascii = static_cast<int>(value);
        std::bitset<CODED_MSG_BITS> binary(ascii);
        return binary.to_string();
    }

    std::vector<int> Lzw_coder::binary_string_to_lzw_indexes(const std::string &binary_str) {
        std::string buffer = binary_str;
        std::vector<int> lzw_indexes{};

        while (!buffer.empty()) {
            std::string coded_char{};

            // Get the binary part of one character from the binary string
            for (int i{0}; i < CODED_MSG_BITS; i++) {
                coded_char.push_back(buffer.front()); // Grab next bit in front and put it in the coded_char "byte"
                buffer.erase(buffer.begin()); // Delete character in the front
            }

            // Convert to char and push to lzw_indexes vector
            std::bitset<CODED_MSG_BITS> binary(coded_char);
            auto int_value = binary.to_ulong();
            lzw_indexes.push_back(int_value);
        }

        return lzw_indexes;
    }
}