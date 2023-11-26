#include "file_handler.h"

namespace files {

    bool File_handler::open(const std::string &file_name) {
        file_in.open(file_name);

        if (!file_in) {
            // File has not been opened successfully
            return false;
        } else {
            // Read current contents into file_buffer
            while (file_in.peek() != EOF) {
                buffer.push_back((char) file_in.get());
            }

            file_in.close();
            return true;
        }
    }

    bool File_handler::write(const std::string &file_name) {
        file_out.open(file_name);

        if (!file_out) {
            // File has not been created/opened successfully
            return false;
        } else {
            file_out << buffer; // Write buffer back into file
            buffer.clear(); // Clear buffer

            file_out.close();
            return true;
        }
    }

    bool File_handler::write_bits(const std::string &file_name) {
        file_out.open(file_name);

        if (!file_out) {
            // File has not been created/opened successfully
            return false;
        } else {
            std::string output_chars{};


            // The buffer consists of a long string of bits like "101010100101001010101"
            // While the buffer isn't empty, pop out 8 bits at a time, convert this to a char representation
            // of the bits, and save this to the output string
            while (!buffer.empty()) {
                std::string temp (8, '0');

                // Put 8 bits in the string
                if(buffer.length() >= 8) {
                    for (int i{}; i < 8; i++) {

                        char c = buffer.front(); // Get character from the front
                        buffer.erase(buffer.begin()); // Delete character in the front

                        temp[i] = c;
                    }
                } else {
                    // Length needs to be saved because elements will get deleted in subsequent runs through the for loop
                    // Therefore we can't use buffer.length() as the index condition
                    auto current_length = buffer.length();
                    for (int i{}; i < current_length; i++) {
                        auto test = buffer.length();
                        char c = buffer.front(); // Get character from the front
                        buffer.erase(buffer.begin()); // Delete character in the front

                        temp[i] = c;
                    }
                }

                // Convert the temp_str from bits to a character and add it to output_chars string
                output_chars.push_back(binary_string_to_char(temp));
            }

            file_out << output_chars; // Write buffer back into file

            file_out.close();
            return true;
        }
    }

    char File_handler::binary_string_to_char(const std::string &binary_string) {
        int int_value = std::stoi(binary_string, nullptr, 2);
        return static_cast<char>(int_value);
    }

}