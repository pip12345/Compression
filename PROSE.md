# Compression: Huffman coding and the LZW algorithm
## By: Floris de Bruin (438652) - Dec. 2023 - Course: Advanced Programming Concepts

#
**Overview:**
```text
Content:
+ 1. Introduction
+ 2. Design overview
+ 3. Huffman coding
    - 3.1 Introduction
    - 3.2 Theory behind the algorithm
    - 3.3 Implementation in the program
        - 3.3.1 Program overview
        - 3.3.2 Frequency table: counting letters
        - 3.3.3 Building the tree
        - 3.3.4 Decoding table: tree traversal
        - 3.3.5 Encoding
        - 3.3.6 Decoding
+ 4. The LZW (Lempel–Ziv–Welch) algorithm
    - 4.1 Introduction
    - 4.2 Theory behind the algorithm
    - 4.3 Implementation in the program
        - 4.3.1 Program overview
        - 4.3.2 Encoding
        - 4.3.3 Decoding
+ 5. File handling
+ 6. Evaluation
+ 7. References
```
---
## 1. Introduction
The purpose of the assignment is implementing the compression and decompression of files using the 
Huffman coding algorithm and the LZW (Lempel–Ziv–Welch) algorithm.
The learning objectives are to implement both these algorithms, and an interface to encode and decode
text files in order to test these algorithms.

The core subject of this assignment is compression. Compression is the process of reducing the size of a file by 
encoding information in a more efficient way. It removes redundant or unnecessary data, allowing the file to take up 
less storage space. Compression is at its core about finding patterns and redundancy within data and reducing these 
redundancies. Both to-be-covered algorithms are lossless, which means that no data may be lost after a cycle of 
compression and decompression. 
---
## 2. Design Overview

Above is an image of the total program developed for this assignment. The program contains:

- Two algorithms (LZW and Huffman) for compressing and decompressing files
- A file handler to manage opening, reading and writing binary to/from files
- An encompassing compression handling class that incorporates all the above elements into simple to use functions.


<div style="display: flex">
<img style="margin: auto" src="docs/img/Overview.png" alt="UML overview of the program" width="10910"/>
</div>
<div style="text-align: center;">
Figure 1: UML Overview of the program (public methods only)
</div>


---
## 3. Huffman coding
### 3.1 Introduction
Huffman coding is an algorithm that efficiently assigns variable-length codes to different characters in a text file, 
where more frequent characters receive shorter codes, reducing overall space while retaining the original information.

The downside of this algorithm is that the data used to encode the text has to be included with the encoded text in order 
to be able to decode it. This is a permanent overhead that leads to worse compression ratios for smaller files.

### 3.2 Theory behind the algorithm

Compressing a file using Huffman coding works as follows:

1. _Building the frequency table_: The algorithm starts by analyzing the text to determine the frequency of 
each character. Each character will get assigned a unique code depending on their frequency.
More frequent characters will be assigned a shorter code, and less frequent ones will have longer codes.


2.  _Building the Huffman tree_: After building the frequency table, a tree is built using an 
algorithm that walks through the frequency table and merges the two least frequent characters at each step until all characters are merged and form a 
single tree. 


3. _Building the coding table_: Once the Huffman tree is built, each character in the tree (leaf nodes) receives a unique binary code. 
These codes are derived by traversing the tree from the root to each character, assigning '0' for the left branch and '1' 
for the right branch.


4. _Encoding the text_: With the codes assigned, the original data is then encoded by replacing each character with its corresponding 
Huffman code. This compressed representation is smaller than the original data, especially when frequent characters are 
represented by shorter codes. The resulting encoded text has either the coding or frequency table included in order to decode the text.

Decoding is simply the same process in reverse if the frequency table is included, or in the case the coding table is included
the step of building the tree again is skipped.

- Decoding with the frequency table: Using the included frequency table, the Huffman tree is built. The tree is then traversed
according to the "instructions" in the encoded data. The encoded data essentially forms a route from the root of the tree to a leaf node.
Each 0 is a left turn and each 1 is a right turn. The letter corresponding to the leave node at the end destination is the decoded letter.


- Decoding with the coding table: This is a direct approach that doesn't require rebuilding the tree, at the cost of
extra overhead that has to be saved with the encoded data. The encoded data can simply be read out and compared with
the codes in the coding table, and decoded.

In order to get consistent encoding and decoding results, some extra rules may be put in place that aren't necessarily
part of the Huffman algorithm, such as ordering equal weighted leaf nodes alphabetically when constructing the tree.
These rules are implementation dependent, therefore the exact implementation must be known in order to decode a Huffman
encoded text.

### 3.3 Implementation in the program
#### 3.3.1 Program overview
The Huffman coding part of the program consists of the following classes:
- _Huffman_coder_: Generates the frequency table, and encodes/decodes strings using the coding table generated by Tree
- _Tree_: Builds a tree out of a passed frequency table, then generates the coding table by walking through the tree using a recursive pathing function.

The activity diagram below shows the interaction between both classes during encoding and decoding.

<div style="display: flex">
<img style="margin: auto" src="docs/img/Activity diagram Huffman.png" alt="Activity diagram of Huffman code" width="500"/>
</div>
<div style="text-align: center;">
Figure 2: Activity diagram of Huffman_coder and Tree
</div>

#### 3.3.2 Frequency table: counting letters

blabla text about node

```c++
    // Min heap node in the huffman tree
    struct Node {
        int freq;
        char data;
        Node *left{nullptr};
        Node *right{nullptr};

        Node(char data, int freq) {
            this->freq = freq;
            this->data = data;
        }
    };
```

blablabla text about frequency counting and converting it to a std::vector<Node>

```c++
    std::vector<Node> Huffman_coder::string_to_nodes(const std::string &text_str) {
        /// Count the frequency of each character, output map is sorted alphabetically first

        std::map<char, int> freq_map; // holds a map of each character and its frequency, sorted alphabetically
        std::vector<std::pair<char, int>> freq_sorted{}; // Sorted by-frequency vector of the map
        std::vector<Node> nodes{};

        // Traverse the string
        for (int i{0}; text_str[i]; i++) {
            // If the current character hasn't been found before, set frequency to 1
            if (freq_map.find(text_str[i]) == freq_map.end()) {
                freq_map.insert(std::make_pair(text_str[i], 1));
            } else {
                // If the character already exists in the map, increase the frequency
                freq_map[text_str[i]]++;
            }
        }

        // Copy map into vector
        for (auto &it: freq_map) {
            freq_sorted.push_back(it);
        }

        // Sort by frequency
        std::sort(freq_sorted.begin(), freq_sorted.end(), cmp_map_sort);
        
        /// Convert sorted vector to nodes and add them to nodes vector
        for (auto &it: freq_sorted) {
            Node temp(it.first, it.second);
            nodes.push_back(temp);
        }

        return nodes;
    }
```

#### 3.3.3 Building the tree

blablabla tree is built from a min_heap

in class:
```c++
// Min priority queue (min heap) used for building and storing the Huffman tree
        std::priority_queue<Node *, std::vector<Node *>, Node_compare> min_heap{};
```

blablabla freq table is first added to the min_heap

```c++
    void Tree::add_freq_table(const std::vector<Node> &n) {
        // Wipe current contents of min heap (tree)
        clear_min_heap();

        // Add new freq_table to min_heap
        for (auto i: n) {
            min_heap.push(new Node(i.data, i.freq));
        }
        build_tree();
    }
```

blablabla then build a tree from it

```c++
    void Tree::build_tree() {
        // Iterate while heap has elements
        while (min_heap.size() > 1) {
            // Extract the 2 lowest freq items from heap
            left = min_heap.top();
            min_heap.pop();

            right = min_heap.top();
            min_heap.pop();

            // Add a new root node to these two nodes with the frequency being the sum of the frequency of both left and right children
            // '~' character reserved for indicating the root node
            root = new Node('~', left->freq + right->freq);
            root->left = left;
            root->right = right;

            // Push new tree part back into the min heap
            min_heap.push(root);
        }
    }
```

#### 3.3.4 Decoding table: tree traversal

blablabla it's a recursive tree traversal algorithm and yeets everything into a map

```c++
    void Tree::coding_table_from_node(Node *n, const std::string& code_recursive, std::map<char, std::string> &coding_table) {
        // If null, we've reached the end, break from recursion
        if (n == nullptr) {
            return;
        }

        // Only output if it's not a root node
        if (n->data != '~') {
            coding_table.insert(std::make_pair(n->data, code_recursive));
        }

        coding_table_from_node(n->left, code_recursive + "0", coding_table); // Left child, add a 0 to the code
        coding_table_from_node(n->right, code_recursive + "1", coding_table); // Right child, add 1 to the code
    }
```

Blahblah words
#### Example tree:

Below is an example tree generated by the code for the word "programming". The blue nodes are root nodes that include the sum
of the total frequencies of all its child nodes. The purple leaf nodes are the characters.  When traversing the tree,
a left branch is a '0' and a right branch is a '1'. The results of the generated codes for each character

<div style="display: flex">
<img style="margin: auto" src="docs/img/Alphabetically ordered single frequencies.png" alt="Generated tree for the word Programming" width="7610"/>
</div>
<div style="text-align: center;">
Figure 3: Generated tree and code table for the word Programming
</div>

#### 3.3.5 Encoding

blablabla use coding table to find the corresponding code for each character in the string

```c++
    std::string Huffman_coder::code_with_coding_table(const std::string &text_str,
                                                      const std::map<char, std::string> &coding_table) {

        std::string coded{};

        for (auto i: text_str) {
            coded.append(coding_table.find(i)->second);
        }

        return coded;
    }
```

#### 3.3.6 Decoding

blablabla words

```c++
    std::string Huffman_coder::decode_with_coding_table(std::string encoded_text_str,
                                                        const std::map<char, std::string> &coding_table) {

        std::string read_buffer{};
        std::string output_string{};
        auto reversed_table = reverse_map(coding_table);

        // We will copy an element from encoded_text_str to read_buffer, then remove it from the encoded_text_str
        // Read_buffer will be checked to the coding table:
        // If the contents of read_buffer are equal to the code of a character from the coding table,
        // then the corrresponding character will be added to the output string and read_buffer will be wiped
        // This will continue until encoded_text_str is empty;

        // add a code number to the buffer until it is something that exists inside the coding table
        while (!encoded_text_str.empty()) {
            read_buffer.push_back(encoded_text_str.front()); // Add front element of encoded text to read buffer

            encoded_text_str.erase(encoded_text_str.begin()); // delete front element from encoded text

            // Check if the code contents of read buffer correspond to a character in the map
            // map.find() returns the end iterator if nothing is found

            // If the value exists
            if (reversed_table.find(read_buffer) != reversed_table.end()) {

                // add the corresponding character of the code to the output string
                output_string.push_back(reversed_table.find(read_buffer)->second);

                // Wipe the read_buffer
                read_buffer.clear();
            }
        }

        if (!read_buffer.empty()) {
            std::cerr
                    << "read_buffer wasn't empty, therefore a character was in the decoding string that wasn't encoded in the coding table!";
        }

        return output_string;
    }
```


---

## 4. The LZW (Lempel–Ziv–Welch) Algorithm
### 4.1 Introduction
The LZW (Lempel-Ziv-Welch) algorithm is a dictionary-based compression algorithm. It works by replacing sequences of data with codes, 
building a dictionary of these sequences as it walks through it. When it encounters a repeated sequence, it outputs the corresponding 
code. This method effectively reduces the size of the data by storing repeated patterns more efficiently.

What is meant by a "sequence of data" can be anything from words such as "the" which can appear hundreds of times
in a large text, to simply a small combination of letters such as "th", "ck" and "nk", which usually appear in many different words.
By encoding these with a single code that is less bits than the individual characters on their own, compression is attained.

The largest advantage of LZW over Huffman is that the encoded data doesn't need any added frequency table or "code book" 
to decode it. The dictionary used to encode a file with LZW can be rebuilt while decoding it. 
This reduces the overhead significantly by eliminating the need to store extra data with the encoded text.

### 4.2 Theory behind the algorithm

Compressing a file with LZW works as follows:

1. _Initialization_: The algorithm initializes a dictionary containing all 256 default ASCII characters. Each symbol takes a unique code which is equal to their position in the dictionary.


2. _Building the dictionary_: The algorithm scans the input data and looks for sequences of characters that repeat. When a sequence is found for the first time, it adds it to the dictionary and assigns it the next available position/code in the dictionary. It keeps doing this for subsequent sequences, updating the dictionary and generating new codes as needed.


3. _Encoding_: As the dictionary is being built, the resulting code for each sequence of characters is output to a file. This is the encoded file.


4. _Decoding_: To decode the compressed data, the receiver uses the same default initialized dictionary to decode first (and therefore known) characters of the file. 
Since each subsequent sequence of characters is created from this known initial set, the entire dictionary can be rebuilt.


LZW's efficiency relies on its ability to create new codes for longer sequences of characters encountered,  reducing the overall size of the data.
Both encoder and decoder must use the same initial dictionary and follow the same rules for encoding/decoding to ensure the dictionary is constructed the same way each time.

Since the code for the encoded data takes the value of the position in the dictionary, the size of the dictionary determines
the level of compression possible. The dictionary is usually between 12 - 16 bits. This is also the number of bits
each "code" is takes up in the compressed data.

This means that a larger dictionary allows more unique sequences of characters to be saved therefore allowing more compression. However, for smaller files with very litle
repeating sequences of characters, using a large dictionary size will hurt the total attainable compression ratio.

### 4.3 Implementation in the program
#### 4.3.1 Program overview

- note to self: make an activity diagram pls

#### 4.3.2 Encoding

blablabla some words about how encoding works

```c++
    std::string LZW_coder::encode(const std::string &text_str) {
        std::map<std::string, int> dict{};
        int dict_size = 256;
        std::string coded_msg{};
        std::string first_input{}; // String because we need to be able to append characters: 't' + 'h' = "th"
        bool overflow_flag{false};

        // Build default dictionary
        for (int i{0}; i < dict_size; i++) {
            dict[std::string{(char) i}] = i;
        }

        // Encode the text_str
        for (int i{0}; i < text_str.length(); i++) {
            char next_input = text_str[i];

            // If first_input + next_input is in the dictionary
            if (dict.count(first_input + next_input)) {
                first_input += next_input;
            } else if (dict_size <= pow(2, LZW_CODED_MSG_BITS)) {
                // Output code
                coded_msg.append(int_to_binary_str(dict[first_input]));

                // Add first_input + next_input to the dictionary by setting new fake "ascii" value
                dict[first_input + next_input] = dict_size++;
                first_input = next_input;
            } else {
                // If the dictionary is full, stop filling it and encode the rest of the file using the current dictionary
                //coded_msg.append(int_to_binary_str(dict["a"]));
                coded_msg.append(int_to_binary_str(dict[first_input]));
                first_input = next_input;
                if (!overflow_flag) {
                    std::cerr << "\nDictionary Overflow, increase LZW_CODED_MSG_BITS!";
                    overflow_flag = true;
                }
            }
        }

            // Print the last character
            if (!first_input.empty()) {
                coded_msg.append(int_to_binary_str(dict[first_input]));
            }

            return coded_msg;
        }
```

#### 4.3.3 Decoding

blablabla some more words about how decoding works

```c++
        std::string LZW_coder::decode(const std::string &encoded_text_str) {
            std::map<int, std::string> dict{};
            std::string first_input{};
            std::string decoded_msg{};
            std::string temp{};

            int dict_size = 256;

            // Convert binary string to lzw index where each int is the char value of the dictionary
            auto lzw_indexes = binary_string_to_lzw_indexes(encoded_text_str);

            // Build default dictionary
            for (int i{0}; i < dict_size; i++) {
                dict[i] = (char) i;
            }

            // Set initial conditions (first character is always known)
            first_input = dict[lzw_indexes[0]];
            decoded_msg = dict[lzw_indexes[0]];

            // Continue on and decode from the 2nd
            for (int i{1}; i < lzw_indexes.size(); i++) {
                int next_input = lzw_indexes[i];

                if (dict.count(next_input)) {
                    temp = dict[next_input];
                } else {
                    temp = first_input + first_input[0];
                }

                decoded_msg += temp;
                dict[dict_size++] = first_input + temp[0];
                first_input = temp;
            }

            return decoded_msg;
        }
```

---

## 5. File handling
- Something about writing bits directly in a file
- CTRL + Z character triggering EOL in Windows (0x1A) -> fix with std::ios::binary

---

## 6. Evaluation

---

## 7.References
- GeeksforGeeks. *Huffman Coding | Greedy Algo-3*. "https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/", accessed 24 Nov. 2023.
- GeeksforGeeks. *LZW (Lempel–Ziv–Welch) Compression technique*. https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/, accessed 2 Dec. 2023.
- Pizzey Technology. *Huffman coding step-by-step example*. https://www.youtube.com/watch?v=iEm1NRyEe5c, accessed 21 Nov 2023.
- TechRetox. *Lempel-Ziv-Welch Compression Algorithm - Tutorial*. https://www.youtube.com/watch?v=j2HSd3HCpDs, accessed 1 Dec 2023.

