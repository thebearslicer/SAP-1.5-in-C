#include <stdio.h>
#include <stdbool.h>

/*
SAP-1.5 by TheBearSlicer
3/3/2021
0 = noop
1 = HLT
2 = LDI
3 = LDA
4 = ADD
5 = STA
6 = SUB
7 = OUT
8 = JMP
9 = JC
*/
int main() {

    short int accumlator;
    short int b_register;
    short int program_counter;
    short int memory_address_register;
    short int instruction_register;
    short int output_register;
    bool carry_flag;

    //Setup
    accumlator = 0;
    b_register = 0;
    program_counter = 0;
    memory_address_register = 0;
    short int RAM[16] = {
        0, 0, 0, 0,
        0, 0, 0, 0, 
        0, 0, 0, 0, 
        0, 0, 0, 1};
    instruction_register = 0;
    output_register = 0;
    carry_flag = false;
    bool running = true;
    //run

    while (running) {
        printf("OUTPUT = %hd\n", output_register);
        memory_address_register = program_counter;
        instruction_register = RAM[memory_address_register];


        switch (instruction_register)
        {
        case 0:
            program_counter += 1;
            break;

        case 1:
            running = false;
            break;

        case 2:
            accumlator = RAM[memory_address_register + 1];  //LDI
            program_counter += 2;
        
        case 3:
            accumlator = RAM[RAM[memory_address_register + 1]];       //LDA                 //LDA
            program_counter += 2;

        case 4:
            accumlator = accumlator + RAM[RAM[memory_address_register + 1]];        //ADD
            if (accumlator > 255) {
                carry_flag = true;
            }
            if (accumlator < 255) {                 
                carry_flag = false;
            }
            program_counter += 2;

        case 5:
            RAM[RAM[memory_address_register + 1]] = accumlator;         //STA
            program_counter += 2;

        case 6:
            accumlator = accumlator - RAM[RAM[memory_address_register + 1]];        //SUB
            program_counter += 2;

        case 7:
            output_register = accumlator;           //OUT
            program_counter += 1;

        case 8:
            program_counter = RAM[RAM[memory_address_register + 1]]; //JMP

        case 9:
            if (carry_flag == true) {
                program_counter = RAM[RAM[memory_address_register + 1]];
            }                                                   //JC
            if (carry_flag == false) {
                program_counter += 2;
            }
        default:
            break;
        }

    }
    return 0;
}