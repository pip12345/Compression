#include <iostream>
#include <string>
#include "lzw.h"
#include "huff.h"
#include "file_handler.h"

#define WINDOWS

int main() {
    files::File_handler file;
    huff::Huffman_coder hcoder;

    std::string compress_file = "../alice_in_wonderland.txt";

    // Remove extension
    std::string compress_file_no_extension = compress_file.substr(0, compress_file.find(".txt")); // remove .txt

    // Extensions huffman
    std::string extension_compressed = "_compressed.piph";
    std::string extension_freqtable = "_compressed.piphf";
    std::string extension_decompressed = "_decompressed.txt";

    /*** Compression ***/
    // Write encoded file
    file.write_bits(compress_file_no_extension + extension_compressed, hcoder.encode(file.open(compress_file)));

    // Write frequency table
    file.write(compress_file_no_extension + extension_freqtable, hcoder.return_freq_table_str(file.open(compress_file)));

    /*** Decompression ***/
    auto coded_text = file.open_bits(compress_file_no_extension + extension_compressed, compress_file_no_extension + extension_freqtable);
    auto freqtable = file.open(compress_file_no_extension + extension_freqtable);
    file.write(compress_file_no_extension + extension_decompressed, hcoder.decode(coded_text, freqtable));
    ///std::cout << hcoder.decode(coded_text, freqtable);

    //std::cout << file.open_bits("../test_compressed.piph", "../test_compressed.piphf");

    std::string input_message = "Programming gamer time";

    std::cout << "\nInput string:   " << input_message << std::endl;
    auto input_message_coded = hcoder.encode(input_message);
    auto input_message_freqtable = hcoder.return_freq_table_str(input_message);
    std::cout << "Output coded_text:   " << input_message_coded << std::endl;

    auto input_message_decoded = hcoder.decode(input_message_coded, input_message_freqtable);
    std::cout << "Output decoded: " << input_message_decoded << std::endl;

    std::cout << "\nDone!" << std::endl;
}