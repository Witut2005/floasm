

#include <map>
#include <stdint.h>


std::pair<uint8_t, std::string> one_segment_opcode[0x10] = 
{
    {0x40,"$ax++"},
    {0x41,"$cx++"},
    
    {0x42,"$dx++"},
    {0x43,"$bx++"},
    
    {0x44,"$sp++"},
    {0x45,"$bp++"},
    
    {0x46,"$si++"},
    {0x47,"$di++"},


    {0x48,"$ax--"},
    {0x49,"$cx--"},
    
    {0x4A,"$dx--"},
    {0x4B,"$bx--"},
    
    {0x4C,"$sp--"},
    {0x4D,"$bp--"},
    
    {0x4E,"$si--"},
    {0x4F,"$di--"}

    
};


enum two_segment_opcode
{
    mov = 0x8b,
    add = 0x3,
    sub = 0x2b
};
