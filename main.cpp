#include <iostream>
#include <string>
#include "lzw.h"
#include "huff.h"
#include "file_handler.h"

#define WINDOWS

int main() {
    files::File_handler file;
    huff::Huffman_coder hcoder;
    lzw::Lzw_coder lzwcoder;

    std::string compress_file = "../test_txt/alice_in_wonderland.txt";

    // Remove extension
    std::string compress_file_no_extension = compress_file.substr(0, compress_file.find(".txt")); // remove .txt

    // Extensions huffman
    std::string extension_compressed = "_compressed.piph";
    std::string extension_freqtable = "_compressed.piphf";
    std::string extension_decompressed = "_decompressed_h.txt";

    // Extensions LZW
    std::string extension_compressed_lzw = "_compressed.pipl";
    std::string extension_decompressed_lzw = "_decompressed_l.txt";


    /*** Huffman Compression ***/
    // Write encoded file
    file.write_bits(compress_file_no_extension + extension_compressed, hcoder.encode(file.open(compress_file)));

    // Write frequency table
    file.write(compress_file_no_extension + extension_freqtable, hcoder.return_freq_table_str(file.open(compress_file)));

    /*** Huffman Decompression ***/
    auto coded_text = file.open_bits(compress_file_no_extension + extension_compressed, compress_file_no_extension + extension_freqtable);
    auto freqtable = file.open(compress_file_no_extension + extension_freqtable);
    file.write(compress_file_no_extension + extension_decompressed, hcoder.decode(coded_text, freqtable));

    /*** LZW Compression ***/
    // Write encoded file
    file.write_bits(compress_file_no_extension + extension_compressed_lzw, lzwcoder.encode(file.open(compress_file)));

    /*** LZW Decompression ***/
    auto coded_text_lzw = file.open_bits(compress_file_no_extension+extension_compressed_lzw);
    auto decoded_text_lzw = lzwcoder.decode(coded_text_lzw);
    file.write(compress_file_no_extension + extension_decompressed_lzw, decoded_text_lzw);

    //std::cout << hcoder.decode(coded_text, freqtable);
    //std::cout << "Bits:\n" << coded_text << std::endl;
    //std::cout << "\nFreq table:\n" << freqtable;

    std::cout << "\nDone!" << std::endl;
}