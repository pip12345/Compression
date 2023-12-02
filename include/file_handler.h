#ifndef COMPRESSION_FILE_HANDLER_H
#define COMPRESSION_FILE_HANDLER_H

#include <fstream>
#include <sstream>
#include <string>

namespace files {

/// Put this in own header file because it needs to include huffman and lzw and stuff later
//    class Compression_handler {
//    public:
//        bool Huffman_file_encode(const std::string& file_name);
//        bool Huffman_file_decode(const std::string& file_name);
//
//    private:
//    };

    // Opens a file and loads it into the buffer, this buffer can then be modified.
    // Afterwards, the buffer can be written back into a file.
    class File_handler {
    public:
        std::string open(const std::string& file_name); // Opens the file with the specified file_name, returns contents of file
        bool write(const std::string& file_name, const std::string& to_write); // Writes the contents to_write with the specified filename, returns false in case of writing error

        std::string open_bits(const std::string &file_name); // Open, converts the chars in the file to a binary representing string, and returns it
        std::string open_bits(const std::string &file_name, const std::string& frequency_table_str); // Open, converts the chars in the file to a binary representing string, and returns it. Uses frequency table total char count for huffman coded messages
        bool write_bits(const std::string& file_name, const std::string &to_write); // Write, but interprets the contents of to_write as individual bits and converts them to chars, returns false in case of writing error

    private:
        std::ifstream file_in{};
        std::ofstream file_out{};

        char binary_string_to_char(const std::string& binary_string);

    };
}

#endif //COMPRESSION_FILE_HANDLER_H
