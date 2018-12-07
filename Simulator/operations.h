/* File contains the function to execute the instructions passed in the MIPS program. */
#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
using namespace std;
#define MAX_INSTR (BGE+1)
#define MAX_STR 100
string entry = "main";
int total = 0;

int INST_ALU = 0, INST_JUMP = 0, INST_BRANCH = 0, INST_MEM = 0, INST_OTHER = 0;
int runBenchmark();
// Arithmetic operations 
void add (int dest,int reg1,int reg2);		// Stores the sum of values in reg1 and reg2 in dest.
void sub (int dest,int reg1,int reg2);		// Stores the difference of values in reg1 and reg2 in dest.
void and_(int dest,int reg1,int reg2);		// Stores the 'and' of values in reg1 and reg2 in dest.
void slt (int dest,int reg1,int reg2);		// Stores the slt of values in reg1 and reg2 in dest.
void or_ (int dest,int reg1,int reg2);		// Stores the 'or' of values in reg1 and reg2 in dest.
void sll(int dest, int reg1, int reg2);
void mul(int dest, int reg1, int reg2);
void div(int dest, int reg1, int reg2);
// Load Immediate
void li(int dest,int val);

// Load/Store instruction
void load_word(int dest,int addr, int offset);
void store_word(int dest,int addr, int offset);

// Branch & Jump instructions
void jump(int num);
void jr(int num);
void jal(int num);
void beq(int reg1, int reg2, int pc_dest);
void bne(int reg1, int reg2, int pc_dest);
void blt(int reg1, int reg2, int pc_dest);
void ble(int reg1, int reg2, int pc_dest);
void bgt(int reg1, int reg2, int pc_dest);
void bge(int reg1, int reg2, int pc_dest);
// Syscall
void syscall();

// Move instruction
void move(int dest,int src);

struct instruct_mem_element
{
	int cod[4];
	char*c;
};


struct instruct_mem
{
	struct instruct_mem_element mem[2048];
};

struct label_table
{
	struct label_element {
		string name;
		int inst_num;
	}label[100];
}labels;

int label_num;

/********* FUNCTIONS TO ENCODE-DECODE THE INSTRUCTION ************/

void encode(char*input, int *coded, int num);	 //Function to convert text into opcodes.
void decode(int*encoded_inst);	// Decode and perform the instructions.

													/*****************************************************************/


													/********** FUNCTIONS TO LOAD & EXECUTE THE INSTRUCTIONS *********/

int read_file(FILE*file);
void load_instruct_mem(int mem_pos, int*instruct);  //Function to load the instruction into the instruction memory. 
void execute(int fin);

int label_pos(char*name);			// Returns the index of the label structure storing the label-name

int pc;

struct reg
{
	string alt_name;			// Stores names like $t0, $fp, $at
	int val;
};


struct reg reg_file[32];


void init_reg_file();	   // To initialise the register file (This is has to be called before the first reference to registers)
int reg_num(char*alt_name);	// Returns the number of the register given the alternate name.

enum Instruction
{
	NOP, ADD, ADDU, ADDIU, SUB, SUBU, SUBIU, SLT, SLTI, SLL, MUL, DIV, AND, OR, ORI, SYSCALL, LW, SW, LI, LA, MOVE, J, JAL, JR, BEQ, BNE, BLT, BLE, BGT, BGE
};
const string Instr[] = { "nop", "add", "addu", "addiu", "sub", "subu", "subiu", "slt", "slti", "sll", "mul", "div", "and", "or", "ori", "syscall", "lw", "sw", "li", "la", "move", "j", "jal", "jr", "beq", "bne", "blt", "ble", "bgt", "bge" };

map<string, string> strings[MAX_STR];
struct instruct_mem *im = new instruct_mem;
map<int, int> dm;

 #endif		//End of file
