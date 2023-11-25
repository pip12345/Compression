#include <iostream>
#include <string>
#include "lzw.h"
#include "huff.h"
#include "file_handler.h"

int main() {
    files::File_handler file;
    huff::Huffman_coder hcoder;

    std::string words{};

    if(file.open("../test.txt")) {

        // Do something to the buffer here
        file.buffer << "testsomemore";

        file.write("../test_compressed.txt");
    } else {
        std::cout << "lol error" << std::endl;
    }

    std::cout << hcoder.encode("Programming");


    std::cout << "\nDone!" << std::endl;
}