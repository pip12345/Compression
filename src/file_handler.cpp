#include "file_handler.h"

namespace files {

    bool File_handler::open(const std::string& file_name) {
        file_in.open(file_name);

        if (!file_in) {
            // File has not been opened successfully
            return false;
        } else {
            // Read current contents into file_buffer
            while (file_in.peek() != EOF) {
                buffer << (char) file_in.get();
            }

            file_in.close();
            return true;
        }
    }

    bool File_handler::write(const std::string& file_name) {
        file_out.open(file_name);

        if(!file_out) {
            // File has not been created/opened successfully
            return false;
        } else {
            file_out << buffer.str(); // Write buffer back into file

            file_out.close();
            return true;
        }
    }

}