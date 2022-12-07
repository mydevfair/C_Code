#include <stdio.h>
#include <stdlib.h>
// This is an array of register mnemonics in y86
const char *register_names[] = {"%eax", "%ecx", "%edx",
                                "%ebx", "%esp", "%ebp",
                                "%esi", "%edi", "UNKNOWN_REGSITER"};
// This is the help function that reads y86 binary code from a file
unsigned int loadBinFromFile(const char *filename, unsigned char memory[],
                             unsigned int memsize);

int main(int argc, char **argv) {
    unsigned int MAX_MEMSIZE = 4096;
    unsigned char
            memory[MAX_MEMSIZE]; // This array represents the 4KB memory space
    unsigned int PC = 0;     // This is the initial program counter address

    if (argc < 2) {
        printf(
                "Usage: please specify a y86 binary program file in the argument.\n");
        return -1;
    }

    unsigned int program_size = loadBinFromFile(argv[1], memory, MAX_MEMSIZE);

    if (program_size == 0)
        return 0;

    // TODO: Implement your disassembler from here

    // At the moment, it simply display each byte from the memory.

    while (PC < program_size) {
        int operandA = memory[PC + 1] >> 4; // This reads the leftmost four bits from byte 1 to give the correct register value
        int operandB = memory[PC + 1] % 0x10; // This reads the rightmost four bits from byte 1 to give the correct register value
        // value rearranges bytes 2, 3, 4, 5 from little endian to big endian to give the value of the 32 bit signed integer
        int value = memory[PC + 2] + (memory[PC + 3] << 8) +
                    (memory[PC + 4] << 16) + (memory[PC + 5] << 24);
        // value1 rearranges bytes 1, 2, 3, 4 from litle endian to big endian to give the dest 32bit integer as jump destination
        int value1 = memory[PC + 1] + (memory[PC + 2] << 8) +
                     (memory[PC + 3] << 16) + (memory[PC + 4] << 24);
        // following 3 statemnets are instruction with no operand (1 byte in size)
        if (memory[PC] == 0x00) {
            printf("halt\n"); // prints instruction
            PC += 1; // moves counter on by 1
        } else if (memory[PC] == 0x10) {
            printf("nop\n"); // prints instruction
            PC += 1; // moves counter on by 1
        } else if (memory[PC] == 0x90) {
            printf("ret\n"); // prints instruction
            PC += 1; // moves counter on by 1
            // the following 13 statements are instructions with only register operands (2 bytes in size)
        } else if (memory[PC] == 0x20) {
            printf("rrmovl %s, %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x21) {
            printf("cmovle %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x22) {
            printf("cmovl %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x23) {
            printf("cmove %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x24) {
            printf("cmovne %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x25) {
            printf("cmovge %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x26) {
            printf("cmovg %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x60) {
            printf("addl %s, %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x61) {
            printf("subl %s %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x62) {
            printf("andl %s, %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x63) {
            printf("xorl %s, %s\n", register_names[operandA],
                   register_names[operandB]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0xA0) {
            printf("pushl %s\n", register_names[operandA]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0xB0) {
            printf("popl %s\n", register_names[operandA]); // prints instruction and register values
            PC += 2; // moves counter on by 2
        } else if (memory[PC] == 0x30) {
            printf("irmovl $%d, %s\n", value, register_names[operandB]); // prints instruction and register values + value - 32 bit signed integer
            PC += 6; // moves counter on by 6
        } else if (memory[PC] == 0x40) {
            printf("rmmovl %s, %d(%s)\n", register_names[operandA], value,
                   register_names[operandB]); // prints instruction and register values + value - 32 bit signed integer
            PC += 6; // moves counter on by 6
        } else if (memory[PC] == 0x50) {
            printf("mrmovl %d(%s), %s\n", value, register_names[operandB],
                   register_names[operandA]); // prints instruction and register values + value - 32 bit signed integer
            PC += 6; // moves counter on by 6
        } else if (memory[PC] == 0x70) {
            printf("jmp %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x71) {
            printf("jle %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x72) {
            printf("jl %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x73) {
            printf("je %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x74) {
            printf("jne %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x75) {
            printf("jge %u\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x76) {
            printf("jg %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else if (memory[PC] == 0x80) {
            printf("call %d\n", value1); // prints instructions with intermidiate values as an operand - dest 32 bit integer as jump destination
            PC += 5; // moves counter on by 5
        } else {
            PC++; // moves counter on by one if instruction not recognised
        }
    }

    return 0;
}

/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function reads in a y86 machine bytecode from file and
store them in an unsigned char array.
******************************************************************************/
unsigned int loadBinFromFile(const char *filename, unsigned char memory[],
                             unsigned int memsize) {
    unsigned int bytes_read = 0;

    unsigned int file_size = 0;

    FILE *pfile = fopen(filename, "rb");

    if (!pfile) {
        printf("Unable to load file %s, please check if the path and name are "
               "correct.\n",
               filename);
        return 0;
    }

    fseek(pfile, 0, SEEK_END);
    file_size = ftell(pfile);
    rewind(pfile);

    if (file_size > memsize) {
        printf("Program size exceeds memory size of %d.\n", memsize);
        return 0;
    }

    bytes_read = fread(memory, 1, file_size, pfile);

    if (bytes_read != file_size) {
        printf("Bytes read does not match the file size.\n");
        return 0;
    }

    fclose(pfile);

    return bytes_read;
}
