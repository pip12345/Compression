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

- What is the assignment
- What are the learning objectives
- What are the products


## 2. Design Overview

- UML, give information about the total design top-down



## 3. Huffman coding
### 3.1 Introduction
### 3.2 Theory behind the algorithm
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
- No extra included data necessary to decompress, codebook can be reconstructed on the fly from the compressed message
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



