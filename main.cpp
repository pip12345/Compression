#include <iostream>
#include <string>
#include "lzw.h"
#include "huff.h"
#include "file_handler.h"

int main() {
    files::File_handler file;
    huff::Huffman_coder hcoder;

    std::string words{};

    if (file.open("../test.txt")) {

        // Do something to the buffer here
        auto buffer_coded = hcoder.encode(file.buffer);
        file.buffer = buffer_coded;

        file.write_bits("../test_compressed.pip");
    } else {
        std::cout << "lol error" << std::endl;
    }

    std::string input_message = "Programming gamer time";

    std::cout << "Input string:   " << input_message << std::endl;
    auto input_message_coded = hcoder.encode(input_message);
    auto input_message_freqtable = hcoder.return_freq_table_str(input_message);
    std::cout << "Output coded:   " << input_message_coded << std::endl;

    auto input_message_decoded = hcoder.decode(input_message_coded, input_message_freqtable);
    std::cout << "Output decoded: " << input_message_decoded << std::endl;

    std::cout << "\nDone!" << std::endl;
}