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
10 = INC
*/
int main() {

    unsigned short int accumlator;
    unsigned short int b_register;
    unsigned short int program_counter;
    unsigned short int memory_address_register;
    unsigned short int instruction_register;
    unsigned short int output_register;
    bool carry_flag;

    //Setup
    accumlator = 0;
    b_register = 0;
    program_counter = 0;
    memory_address_register = 0;
    unsigned short int RAM[16] = {
        2, 32767, 4, 15,            
        9, 13, 1, 0,             
        0, 0, 0, 0, 
        0, 7, 1, 2};
    instruction_register = 0;
    output_register = 0;
    carry_flag = false;

    int loop;
    char none;
    //run

    while (program_counter < 17) {
        memory_address_register = program_counter;
        instruction_register = RAM[memory_address_register];



        printf("\n");
        printf("A = %hu\n", accumlator);
        printf("PC = %hu\n", program_counter);
        printf("OUTPUT = %hu\n", output_register);
        printf("IR = %hu\n", instruction_register);
        printf("MAR = %hu\n", memory_address_register);
        printf("Carry = %d\n", carry_flag);
        for(loop = 0; loop < 16; loop++)
            printf("%d ", RAM[loop]);
        printf("\n");


        switch (instruction_register)
        {
        case 0:
            program_counter += 1;
            break;

        case 1:
            program_counter = 17;
            break;

        case 2:
            accumlator = RAM[memory_address_register + 1];  //LDI
            program_counter += 2;
            break;

        case 3:
            accumlator = RAM[RAM[memory_address_register + 1]];       //LDA               
            program_counter += 2;
            break;

        case 4:
            accumlator = accumlator + RAM[RAM[memory_address_register + 1]];        //ADD

            if (accumlator > 32768 ) {
                carry_flag = true;
            }
            program_counter += 2;
            break;

        case 5:
            RAM[RAM[memory_address_register + 1]] = accumlator;         //STA
            program_counter += 2;
            break;

        case 6:
            accumlator = accumlator - RAM[RAM[memory_address_register + 1]];        //SUB
            program_counter += 2;
            break;

        case 7:
            output_register = accumlator;           //OUT
            program_counter += 1;
            break;

        case 8:
            program_counter = RAM[memory_address_register + 1]; //JMP
            break;

        case 9:
            if (carry_flag == true) {
                program_counter = RAM[memory_address_register + 1];
            }                                                   //Jc
            if (carry_flag == false)  {
                program_counter += 2;
            break;
            }

        case 10:
            accumlator += 1;             //INC
            program_counter += 1;    


        default:
            break;
        }

    }
    return 0;
}