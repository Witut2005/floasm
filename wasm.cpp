


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



std::fstream file;
std::fstream output_file;
char opcode[20];
uint32_t line_number = 0;


void compile()
{

    if(strstr(opcode,"END"))
    {
        file.close();
        output_file.close();
        exit(0);        
    }

    else if(strstr(opcode,"BEGIN"))
        return;



    for(int i = 0; i < 0x10;i++)
    {
        if(strcmp(one_segment_opcode[i].second.c_str(),opcode) == 0)
        {
            //std::cout << one_segment_opcode[i].second << std::endl;      
            output_file << one_segment_opcode[i].first;
            return;
        }
    }


    char arr[3];

    if(strstr(opcode, "+=") != nullptr)
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

            return;
 

        }
    
    } 

    else if(strstr(opcode,"db"))
    {
        uint8_t tmp = atoi(opcode);
        std::cout << opcode << std::endl;
        std::cout <<  atoi(opcode) << std::endl;
        output_file << (uint8_t)tmp;
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
        opcode[19] = '\0';
        line_number++;
        compile();
    }

    file.close();
    output_file.close();



}



