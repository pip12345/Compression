#include <iostream>
#include <string>
#include "lzw.h"
#include "file_handler.h"

int main() {
    files::file_handler file;

    std::string words{};

    if(file.open("../test.txt")) {

        // Do something to the buffer here
        file.buffer << "fuck";

        file.write("../test_compressed.txt");
    } else {
        std::cout << "lol error" << std::endl;
    }




    std::cout << "Done!" << std::endl;
}