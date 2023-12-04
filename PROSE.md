# Compression: Huffman coding and LZW

**Overview:**
```text
Content:
+ 1. Introduction
+ 2. Design overview
+ 3. Huffman coding
    - 3.1 Introduction
    - 3.2 Theory behind the algorithm
    - 3.3 Implementation in the program
        - Program overview
        - Building the tree
        - Encoding
        - Decoding
+ 4. LZW algorithm
    - 4.1 Introduction
    - 4.2 Theory behind the algorithm
    - 4.3 Implementation in the program
        - Program overview
        - Encoding
        - Decoding
+ 5. File handling
+ 6. Evaluation
+ 7. References
```

## 1. Introduction
The purpose of the assignment is implementing the compression and decompression of files using the 
Huffman coding algorithm and the LZW algorithm.
The learning objectives are to implement both these algorithms, and an interface to encode and decode
text files in order to test these algorithms.

The core subject of this assignment is compression. Compression is the process of reducing the size of a file by 
encoding information in a more efficient way. It removes redundant or unnecessary data, allowing the file to take up 
less storage space. Compression is at its core about finding patterns and redundancy within data and reducing these 
redundancies. Both to-be-covered algorithms are lossless, which means that no data may be lost after a cycle of 
compression and decompression. 

## 2. Design Overview

- UML, give information about the total design top-down


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

----**HIER NOG DRAWIO PLAATJES VOOR DUIDELIJKHEID**

### 3.3 Implementation in the program
#### 3.3.1 Program overview
- Step by step what we need (freq table, decoding table) and why
- Huffman_coder class
- Tree class

#### Building the tree
#### Decoding table: tree traversal
#### Frequency table: counting letters
#### Encoding
#### Decoding





## 4. LZW algorithm
### 4.1 Introduction
The LZW (Lempel-Ziv-Welch) algorithm is a dictionary-based compression algorithm. It works by replacing sequences of data with codes, 
building a dictionary of these sequences as it walks through it. When it encounters a repeated sequence, it outputs the corresponding 
code. This method effectively reduces the size of the data by storing repeated patterns more efficiently.

The largest advantage of LZW over Huffman is that the encoded data doesn't need any added frequency table or "code book" 
to decode it. The dictionary used to encode a file with LZW can be rebuilt while decoding it. 
This reduces the overhead significantly by eliminating the need to store extra data with the encoded text.

### 4.2 Theory behind the algorithm
### 4.3 Implementation in the program
#### Program overview
#### Encoding
#### Decoding



## 5. File handling
- Something about writing bits directly in a file
- CTRL + Z character triggering EOL in Windows (0x1A) -> fix with std::ios::binary



## 6. Evaluation




## 7.References
- GeeksforGeeks. *Huffman Coding | Greedy Algo-3*. "https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/", accessed 24 Nov. 2023.

https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/
https://cs.carleton.edu/faculty/jondich/courses/cs337_w02/assignments/lzw.html



