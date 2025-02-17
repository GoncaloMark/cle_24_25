#include "utf-8.h"

int utf8_decode(UTF8DecoderState& state, uint16_t byte, uint32_t* codepoint)
{
    if((byte & 0x80) == 0){
        state.number_bytes = 1;
        state.remaining_bytes = 1;
    }

    if((byte & 0xE0) == 0xC0){
        state.number_bytes = 2;
        state.remaining_bytes = 2;  
    }

    if((byte & 0xF0) == 0xE0){
        state.number_bytes = 3;
        state.remaining_bytes = 3;
    }

    if((byte & 0xF8) == 0xF0){
        state.number_bytes = 4;
        state.remaining_bytes = 4;
    }

    if(state.remaining_bytes > 0){
        *codepoint = *codepoint | (byte << (8 * (state.remaining_bytes-1)));
        state.remaining_bytes--;
        
        if(state.remaining_bytes == 0){
            state.codepoint = *codepoint;
            return state.number_bytes;
        }
        return 0;
    }

    return -1;
}


bool utf8_is_letter(uint32_t codepoint)
{
    return !utf8_is_space(codepoint) && (
        (codepoint >= 0x41 && codepoint <= 0x5A) ||  
        (codepoint >= 0x61 && codepoint <= 0x7A) ||
        (codepoint >= 0xC0 && codepoint <= 0xFF) ||   
        (codepoint >= 0x100 && codepoint <= 0x17F) || 
        (codepoint >= 0x180 && codepoint <= 0x24F) || 
        (codepoint >= 0x250 && codepoint <= 0x2AF) || 
        (codepoint >= 0x370 && codepoint <= 0x3FF) || 
        (codepoint >= 0x400 && codepoint <= 0x4FF) || 
        (codepoint >= 0x500 && codepoint <= 0x52F) || 
        (codepoint >= 0x2100 && codepoint <= 0x214F) || 
        (codepoint >= 0x4E00 && codepoint <= 0x9FFF)  
    );
}


bool utf8_is_space(uint32_t codepoint)
{
    return (codepoint == 0x20) || (codepoint == 0x9) || (codepoint == 0xA) || (codepoint == 0xB) ||
    (codepoint == 0xC) || (codepoint == 0xD) || (codepoint == 0x00A0) || (codepoint == 0x2007) || (codepoint == 0x202F) ||
    (codepoint == 0x2060);
}
