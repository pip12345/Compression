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

        std::stringstream buffer{}; // holds contents of opened file
    private:
        std::ifstream file_in{};
        std::ofstream file_out{};
    };

}

#endif //COMPRESSION_FILE_HANDLER_H
