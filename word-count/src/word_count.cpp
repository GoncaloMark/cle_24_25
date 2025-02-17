
#include <iostream>

#include "utf-8.h"
#include "word_count.h"

void word_count(const WordCountFlags& flags, const std::vector<std::string>& files)
{
    // Make sure to use the flags to determine what to count
    // Enter your code here !!!
    for (auto& file : files){
        // std::cout << file << std::endl;

        //test utf 8 decoder

        decoder_state_t state;
        uint16_t byte1 = 0b11100000;
        uint16_t byte2 = 0b10000000;
        uint16_t byte3 = 0b10000000;
        
        uint32_t codepoint = 0x00000000;
        
        int state1 = utf8_decode(state, byte1, &codepoint);
        int state2 = utf8_decode(state, byte2, &codepoint);
        int state3 = utf8_decode(state, byte3, &codepoint);
        
        printf("%d\n", state3);
        
        printf("%x\n", state.codepoint);
    }
}
