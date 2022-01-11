


#include <iostream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <map>


#include "./arch_data.h"
#include "./opcode_list.h"



std::fstream file;
std::fstream output_file;
char opcode[10];



void compile()
{
    for(int i = 0; i < 0x10;i++)
    {


        if(strcmp(one_segment_opcode[i].second.c_str(),opcode) == 0)
        {
            std::cout << one_segment_opcode[i].second << std::endl;      
            output_file << one_segment_opcode[i].first;
            return;
        }
    }


    std::vector<std::string> operator_vector;
    char arr[3];
    char arr2[3];


    if(std::count(opcode,opcode + 10,'=') == 1)
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

                    

                    std::cout << ugabuga << std::endl;

                    *x = 'o';

                    op += regs[ugabuga];

                }

                    //operator_vector.push_back(x);
            }

            output_file << two_segment_opcode[0x0];
            op |= 0xC0;
            output_file << op;


            //operator_vector[0] < operator_vector[1] ? dest =  operator_vector[0] : src = operator_vector[1];
            //operator_vector[0] > operator_vector[1] ? dest =  operator_vector[1] : src = operator_vector[0];  
 

        }
    
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
        compile();


    file.close();
    output_file.close();



}



