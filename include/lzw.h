#ifndef COMPRESSION_LZW_H
#define COMPRESSION_LZW_H

#include <string>
#include <vector>

#define CODED_MSG_BITS 16 // Change this to increase the compression, but at the cost of being able to compress less unique character combinations in total

namespace lzw {

    class Lzw_coder {
    public:
        std::string encode (const std::string& text_str);
        std::string decode (const std::string& encoded_text_str);

    private:
        std::string int_to_binary_str(const int& value);
        std::vector<int> binary_string_to_lzw_indexes(const std::string& binary_str);

    };

}

#endif // COMPRESSION_LZW_H