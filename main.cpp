#include <iostream>
#include <string>
#include "lzw.h"
#include "huff.h"
#include "file_handler.h"

int main() {
    files::File_handler file;

    std::string words{};

    if(file.open("../test.txt")) {

        // Do something to the buffer here
        file.buffer << "testsomemore";

        file.write("../test_compressed.txt");
    } else {
        std::cout << "lol error" << std::endl;
    }

    huff::Tree tree;

    //auto nodes = tree.string_to_nodes("Programming");

    tree.add("Programming");

    tree.print_tree();

    std::cout << "Done!" << std::endl;
}