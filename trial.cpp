#include <iostream>
#include <string>
#include "src/utf8.h" // from the utf8-cpp library

int main() {
    std::string utf8_string = "Hello, 𖹾! This is a test.";
    
    // The library correctly iterates over code points, not bytes.
    for (auto it = utf8_string.begin(); it != utf8_string.end();) {
        // 'code_point' will hold the correct 32-bit Unicode value.
        unsigned int code_point = utf8::next(it, utf8_string.end()); 
        std::cout << "Code point: U+" << std::hex << code_point << std::dec << std::endl;
    }
    
    // Correctly get the number of code points (characters)
    size_t num_chars = utf8::distance(utf8_string.begin(), utf8_string.end());
    std::cout << "Number of characters: " << num_chars << std::endl;
    
    return 0;
}