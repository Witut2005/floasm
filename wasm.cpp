


#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdlib>
#include <stdlib.h>

#include "./arch_data.h"
#include "./opcode_list.h"


uint64_t opcode_counter = 0x0;

std::fstream file;
std::fstream output_file;
char opcode[50];
uint32_t line_number = 0;

#define TAB 0x9
#define SPACE 0x20

uint32_t string_to_decimal(char* str)
{
    uint32_t tmp = 0;
    uint32_t ctr = 1;

    for(int i = strlen(str)-1; i >= 0; i--, ctr *= 10)
    {
        if(str[i] >= '0' && str[i] <= '9')
            tmp += (str[i] - 48) * ctr;
    }


    return tmp;
}

uint64_t string_to_hex(char* str)
{
    uint64_t tmp = 0;
    uint64_t ctr = 1;



    for(int i = strlen(str)-1; i >= 0; i--, ctr *= 0x10)
    {

        if((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f'))
            tmp += hex_values[str[i]] * ctr;

        else 
            return tmp;

    }


    return tmp;
}


void compile()
{

    char arr[3];

    {
        char* x = std::find(opcode, opcode + 50,'\0');

        if(*(x-1) == ':')
        {
            *(x-1) = '\0';
            std::string tmp(opcode);
            label_map.insert({tmp,opcode_counter});
            return;
        }
    
    
    }

    for(int i = 0; i < 0x10;i++)
    {
        if(strcmp(one_segment_opcode[i].second.c_str(),opcode) == 0)
        {
            output_file << one_segment_opcode[i].first;
            opcode_counter += 1;
            return;
        }
    }

 
    if(strstr(opcode,"END"))
    {
        file.close();
        output_file.close();
        std::cout << opcode_counter << std::endl;
        
        exit(0);        
    }



    else if(strstr(opcode,"BEGIN"))
        return;

    else if(opcode[0] == ';')
        return;

    
    else if(strncmp(opcode,"jmp",3) == 0)
    {

        std::cout << "YOUR JUMP: ";
        std::cout << opcode << std::endl;
        output_file << (uint8_t)jmp_far;

        uint64_t tmp_ctr = 0x0;

        for(uint8_t i = 4; i < 50;i++, tmp_ctr++)
        {
            opcode[tmp_ctr] = opcode[i];
        }

        opcode[49] = '\0';

        std::string tmp(opcode);



        std::cout << opcode << std::endl;

        uint16_t tmp_opcode = label_map[tmp];


        output_file.write((char*)&tmp_opcode,sizeof(uint16_t));
        output_file.write("\0\0",sizeof(uint16_t));
        return;
    }
    





    else if(strstr(opcode, "+=") != nullptr)
    {
        if(std::count(opcode,opcode + 10,'$') == 2)
        {
            char* x;
            uint8_t op = 0;
            for(int i = 0; i < 2; i++)
            {
                x = std::find(opcode, opcode + 10,'$');

                if(std::find(opcode, opcode + 10,'$') != nullptr)
                {
                    
                    op = op << 3;

                    strncpy(arr,x,3);

                    std::string ugabuga(arr);

                    *x = 'o';
                    op += regs[ugabuga];
                }
            }

            output_file << (uint8_t)0x3;
            op |= 0xC0;
            output_file << op;

            opcode_counter += 2;

            return;
 
        }
    } 

    if(strstr(opcode, "-=") != nullptr)
    {
        if(std::count(opcode,opcode + 10,'$') == 2)
        {
            char* x;
            uint8_t op = 0;
            for(int i = 0; i < 2; i++)
            {
                x = std::find(opcode, opcode + 10,'$');

                if(std::find(opcode, opcode + 10,'$') != nullptr)
                {
                    
                    op = op << 3;

                    strncpy(arr,x,3);

                    std::string ugabuga(arr);

                    *x = 'o';
                    op += regs[ugabuga];
                }
            }

            output_file << (uint8_t)sub;
            op |= 0xC0;
            output_file << op;

            opcode_counter += 2;

            return;
 

        }
    
    } 




    else if(strstr(opcode,"db "))
    {

        uint8_t tmp;

        if(strstr(opcode,"0x") != nullptr)
        {
            tmp = string_to_hex(opcode);
            printf("%x\n",tmp);
            output_file << (uint8_t)tmp;
            return;
        }

        tmp = string_to_decimal(opcode);
        
        printf("%x\n",tmp);

        output_file << (uint8_t)tmp;
        opcode_counter += 1;
    }

    else if(strncmp(opcode,"dw ",3) == 0)
    {

        uint16_t tmp;

        if(strstr(opcode,"0x") != nullptr)
        {
            tmp = string_to_hex(opcode);
            printf("%x\n",tmp);
            output_file << (uint8_t)tmp;
            return;
        }

        tmp = string_to_decimal(opcode);
        
        printf("%x\n",tmp);

        output_file << (uint16_t)tmp;
        opcode_counter += 2;
    }

    else if(strncmp(opcode,"dd ",3) == 0)
    {


        uint32_t tmp;

        if(strstr(opcode,"0x") != nullptr)
        {
            tmp = string_to_hex(opcode);
            printf("%x\n",tmp);
            output_file.write((char*)&tmp, sizeof(tmp));
            opcode_counter += 4;
        }


    }


    else if(strncmp(opcode,"dq ",3) == 0)
    {


        uint64_t tmp;

        if(strstr(opcode,"0x") != nullptr)
        {
            tmp = string_to_hex(opcode);
            printf("%lx\n",tmp);
            output_file.write((char*)&tmp, sizeof(tmp));
            opcode_counter += 8;
        }


    }



    else if(std::count(opcode,opcode + 10,'=') == 1)
    {
        if(std::count(opcode,opcode + 10,'$') == 2)
        {
            char* x;
            uint8_t op = 0;
            for(int i = 0; i < 2; i++)
            {
                x = std::find(opcode, opcode + 10,'$');

                if(std::find(opcode, opcode + 10,'$') != nullptr)
                {
                    
                    op = op << 3;

                    strncpy(arr,x,3);

                    std::string ugabuga(arr);

                    *x = 'o';
                    op += regs[ugabuga];
                }
            }

            output_file << (uint8_t)0x8b;
            op |= 0xC0;
            output_file << op;

            opcode_counter += 2;
            
            return;
 

        }
    
    } 

    else if(strcmp(opcode,"\0") == 0)
        return;

    else
    {

        std::cout << "line: " << line_number << " ERROR: Unknown opcode\n";

        exit(-1);
    }




}



int main(int argc, char **argv)
{




    if(argc != 2)
    {
        printf("Usage: %s file_to_compile\n", argv[0]);
        exit(-1);
    }

    file.open(argv[1], std::ios::in | std::ios::app);
    output_file.open("out.bin", std::ios::binary | std::ios::out);

   
    if(!file.good())
    {   
        std::cout << "problems with file... " << argv[1] << std::endl;
        exit(1);
    }

    

    while(file.getline(opcode,sizeof(opcode)))
    {
        opcode[49] = '\0';
        
        while(opcode[0] == SPACE || opcode[0] == TAB)
        {
            for(int i = 0; i < 49; i++)
                opcode[i] = opcode[i+1];
        }

        line_number++;
        compile();
    }

    file.close();
    output_file.close();



}



