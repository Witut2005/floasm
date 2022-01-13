


#include <map>
#include <stdint.h>
#include <string>

namespace wasm
{
    
typedef struct
{

    union
    {
        uint16_t bit16;

        struct
        {
            uint8_t h;
            uint8_t l;
        };

    };

}reg_t;    

}

using namespace wasm;

reg_t registers[8];

reg_t* reg_ptr[8];


uint8_t mod_reg_rm;

uint8_t dest;
uint8_t src;

std::string register_names[0x8] = {
    {"$ax"},
    {"$cx"},
    {"$dx"},
    {"$bx"},
    {"$sp"},
    {"$bp"},
    {"$si"},
    {"$di"}
};

std::map<std::string, uint8_t > regs= 
{
    {"$ax",0},
    {"$cx",1},
    {"$dx",2},
    {"$bx",3},
    {"$sp",4},
    {"$bp",5},
    {"$si",6},
    {"$di",7}
};


std::map<char, uint8_t> hex_values = 
{
    {'1',0x1},
    {'2',0x2},
    {'3',0x3},
    {'4',0x4},
    {'5',0x5},
    {'6',0x6},
    {'7',0x7},
    {'8',0x8},
    {'9',0x9},
    {'a',0xa},
    {'b',0xb},
    {'c',0xc},
    {'d',0xd},
    {'e',0xe},
    {'f',0xf}
};


std::map<std::string, uint64_t> label_map;