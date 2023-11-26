#ifndef COMPRESSION_FILE_HANDLER_H
#define COMPRESSION_FILE_HANDLER_H

#include <fstream>
#include <sstream>
#include <string>

namespace files {

    // Opens a file and loads it into the buffer, this buffer can then be modified.
    // Afterwards, the buffer can be written back into a file.
    class File_handler {
    public:
        bool open(const std::string& file_name); // Opens the file with the specified file_name into file_buffer, returns true if opened successfully
        bool write(const std::string& file_name); // Writes the contents of file_buffer into the specified file_name, returns true if written successfully

        ///TODO: open_bits, can always read in chunks of 1 byte because its written in 1 byte, use the included number of characters in freq_table_str with keyword ~
        bool open_bits(const std::string& file_name); // Open, but converts the chars in the file to binary representing strings with bits the characters were made out of
        bool write_bits(const std::string& file_name); // Write, but interprets the contents of file_buffer as individual bits and converts them to chars

        char binary_string_to_char(const std::string& binary_string);

        std::string buffer{}; // holds contents of opened file
    private:
        std::ifstream file_in{};
        std::ofstream file_out{};

    };

}

#endif //COMPRESSION_FILE_HANDLER_H
