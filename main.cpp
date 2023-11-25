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

    std::string input_message = "Programming";

    std::cout << "Input: " << input_message << std::endl;
    auto input_coded = hcoder.encode(input_message);
    std::cout << "Output: " << input_coded << std::endl;

    auto input_decoded = hcoder.decode("010001101111001100101101011100111", "blah blah fix this");

    std::cout << "\nDone!" << std::endl;
}