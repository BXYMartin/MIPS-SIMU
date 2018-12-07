#include "stdafx.h"
#include <iostream>
#include <string>
#include "operations.h"

void printPosition() {
	cout << ">>> Program Encountered Unexpected Runtime Error at " << pc << " Where: ";
	cout << im->mem[pc].cod[0] << " " << im->mem[pc].cod[1] << " " << im->mem[pc].cod[2] << " " << im->mem[pc].cod[3] << endl;
	exit(1);
}

void encode(char*input, int *coded, int num)
{
	string inst;		// Holds the instruction (like add,sub,move,b)
	int j, i = 0;
	char*ptr;
	if (ptr = strchr(input, ':'))
	{
		coded[0] = 0;
		int already_exists = 0;			// Variable that indicates that the label is present in the memory
										// This is done in case a reference is provided to the label before its is entotalered.
		for (; input[i] != *ptr && input[i] != 32; i++)
			inst += input[i];
		for (j = 0; j<label_num; j++)
		{
			if (labels.label[j].name == inst)
			{
				if (labels.label[j].inst_num == -1)
				{
					already_exists = 1;
					labels.label[j].inst_num = num;
					return;
				}
				else
				{
					cout << "Label " << inst << " has been used more than once" << endl;
					exit(4);		// Label re-use
				}
			}
		}

		if (!already_exists)
		{
			labels.label[label_num].name = inst;
			labels.label[label_num].inst_num = num;
			label_num++;
			for (; input[i] == 32 || input[i] == ':' || input[i] == 9; i++);
			if (input[i] == '\n' || input[i] == '\x0' || input[i] == '#')
				return;

		}
	}
	inst.clear();
	for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != 9; i++, j++)
	{
		//Copy the first word 
		inst += input[i];

	}
	for (j = 0; j < MAX_INSTR; j++)
	{
		if (inst == Instr[j])
			break;

	}
	if (j < MAX_INSTR)
		coded[0] = j;	// Allots the opcode of the instruction as per the opcode array (in instruction_mem.h)
	else
	{
		cout << "Unknown Instruction : " << inst << endl;
		exit(3);
	}
	if (coded[0] >= ADD && coded[0] <= OR)
	{
		char reg[3];
		int j;
		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register
																				// It could be an immediate value or a register. If preceded by $, it is a register.
		if (input[i - 1] != '$')
		{
			int val = 0;
			// Get the entire number.
			for (; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#'; i++)
				val = val * 10 + (input[i] - '0');
			coded[1] = 32 + val;
		}
		else
		{
			for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
			{
				reg[j] = input[i];

			}
			reg[j] = '\x0';				// Add NULL character to terminate string
			coded[1] = reg_num(reg);
		}

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register
		if (input[i - 1] != '$')
		{
			int val = 0;
			for (; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#'; i++)
				val = val * 10 + (input[i] - '0');	
			coded[2] = 32 + val;
		}
		else
		{
			for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
			{
				reg[j] = input[i];

			}
			reg[j] = '\x0';				// Add NULL character to terminate string
			coded[2] = reg_num(reg);
		}

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

																				// It could be an immediate value or a register. If preceded by $, it is a register.
		if (input[i - 1] != '$')
		{
			int val = 0, neg = 1;
			// Get the entire number.
			for (; input[i] == 32 && input[i] != 10 && input[i] != '\x0'; i++);
			for (; input[i] == '-' && input[i] != '\x0'; i++) {
				neg = -1;
			}
			for (; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#'; i++)
				val = val * 10 + (input[i] - '0');
			val *= neg;	
			if (neg < 0)
				coded[3] = val;
			else
				coded[3] = 32 + val;
		}
		else
		{
			for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
			{
				reg[j] = input[i];

			}
			reg[j] = '\x0';				// Add NULL character to terminate string
			coded[3] = reg_num(reg);
		} 
	}
	else if (coded[0] == LI)
	{
		char reg[3];
		int j;
		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';	
		coded[1] = reg_num(reg);
		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		coded[2] = 0;
		for (; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#' && input[i] != 9; i++)
		{
			coded[2] = coded[2] * 10 + (input[i] - '0');
		}
		//printf ("%d %d %d",coded[0],coded[1],coded[2]);
	}
	else if (coded[0] == LA) {
		char reg[3], label[20];
		int j;
		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';				// Add NULL character to terminate string
		coded[1] = reg_num(reg);
		for (; input[i] == 32; i++);		// Move to the label
											// Copy the label
		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#' && input[i] != 9; i++, j++)
		{
			label[j] = input[i];
		}
		label[j] = '\x0';				// Add NULL character to terminate string

		coded[2] = -1;
		for (j = 0; j < total ; j++) {
			if (strings[j].begin()->first == label)
				coded[2] = j;
		}
		if (coded[2] == -1)
			cout << "Referenced Uninitialized Label String " << label << endl;
	}
	else if (coded[0] == LW || coded[0] == SW)
	{
		/* These instructions have a register and then a memory destination */

		char reg[3], var_name[20];
		int j, val = 0, neg = 1;

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';				// Add NULL character to terminate string
		coded[1] = reg_num(reg);

		for (; input[i] == ',' || input[i] == 32; i++);		// Move to the memory location given

		for (j = 0; input[i] == '-' || (input[i] >= '0' && input[i] <= '9') && input[i] != '\x0'; i++, j++)
		{
			if (input[i] == '-')
				neg = -1;
			val = val * 10 + input[i] - '0';
		}
		val *= neg;
		if(neg < 0)
			coded[3] = val;
		else
			coded[3] = 32 + val;
		for (; input[i] == '(' || input[i] == 32; i++);
		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';				// Add NULL character to terminate string
		coded[2] = reg_num(reg);
		for (; input[i] == ')' || input[i] == 32; i++);
	}
	else if (coded[0] == MOVE)
	{
		char reg[3];
		int j;

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';				// Add NULL character to terminate string
		coded[1] = reg_num(reg);

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';				// Add NULL character to terminate string
		coded[2] = reg_num(reg);
	}
	else if (coded[0] >= BEQ && coded[0] <= BGE)
	{
		char reg[3];
		char label[20];

		int j;

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register
		if (input[i - 1] != '$')
		{
			int val = 0;
			// Get the entire number.
			for (; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#'; i++)
				val = val * 10 + (input[i] - '0');

			// To store the immediate values numbers greater than or equal to 32 are used.	
			coded[1] = 32 + val;
		}
		else
		{
			for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j < 2 && input[i] != '#' && input[i] != 9; i++, j++)
			{
				reg[j] = input[i];

			}
			reg[j] = '\x0';				// Add NULL character to terminate string
			coded[1] = reg_num(reg);
		}
		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register
		if (input[i - 1] != '$')
		{
			int val = 0, neg = 1;
			// Get the entire number.
			for (; input[i] == 32 && input[i] != 10 && input[i] != '\x0'; i++);
			for (; input[i] == '-' && input[i] != '\x0'; i++) {
				neg = -1;
			}
			for (; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#'; i++)
				val = val * 10 + (input[i] - '0');
			val *= neg;
			// To store the immediate values numbers greater than or equal to 32 are used.	
			if(neg < 0)
				coded[2] = val;
			else
				coded[2] = 32 + val;
		}
		else
		{
			for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j < 2 && input[i] != '#' && input[i] != 9; i++, j++)
			{
				reg[j] = input[i];

			}
			reg[j] = '\x0';				// Add NULL character to terminate string
			coded[2] = reg_num(reg);
		}

		for (; input[i] == ',' || input[i] == 32; i++);		// Move to the label

															// Copy the label
		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#' && input[i] != 9; i++, j++)
		{
			label[j] = input[i];

		}
		label[j] = '\x0';				// Add NULL character to terminate string

		coded[3] = label_pos(label);
	}
	else if (coded[0] >= J && coded[0] <= JAL)
	{
		char label[20];
		int j;

		for (; input[i] == 32; i++);		// Move to the label
											// Copy the label
		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && input[i] != '#' && input[i] != 9; i++, j++)
		{
			label[j] = input[i];
		}
		label[j] = '\x0';				// Add NULL character to terminate string

		coded[1] = label_pos(label);
	}
	else if (coded[0] == JR)
	{
		char reg[3];
		int j;

		for (; input[i] == ',' || input[i] == 32 || input[i] == '$'; i++);		// Move to the next register

		for (j = 0; input[i] != 32 && input[i] != 10 && input[i] != '\x0' && input[i] != ',' && j<2 && input[i] != '#' && input[i] != 9; i++, j++)
		{
			reg[j] = input[i];

		}
		reg[j] = '\x0';				// Add NULL character to terminate string
		coded[1] = reg_num(reg);
	}
	return;
}



void load_instruct_mem(int mem_pos, int*instruct)
{
	int j = 0;
	for (j = 0; j<4; j++)
		im->mem[mem_pos].cod[j] = instruct[j];
}

int runBenchmark() {
	return INST_ALU + INST_OTHER + 2 * (INST_JUMP + INST_BRANCH + INST_MEM);
}

void decode(int*encoded_inst)
{
	switch (encoded_inst[0])
	{
	case ADD:
	case ADDIU:
	case ADDU:
		INST_ALU++;
		add(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case SUBU:
	case SUBIU:
	case SUB:
		if (encoded_inst[3] >= 32 || encoded_inst[3] < 0)
			INST_ALU+=2;
		INST_ALU++;
		sub(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case AND:
		if (encoded_inst[3] > 32799 || encoded_inst[3] < -32768)
			INST_ALU++;
		INST_ALU++;
		and_(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case ORI:
	case OR:
		if (encoded_inst[3] > 32799 || encoded_inst[3] < -32768)
			INST_ALU++;
		INST_ALU++;
		or_(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case SLL:
		if (encoded_inst[3] > 32799 || encoded_inst[3] < -32768)
			INST_ALU++;
		INST_ALU++;
		sll(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case MUL:
		if (encoded_inst[3] >= 32 || encoded_inst[3] < 0)
			INST_ALU++;
		INST_ALU++;
		mul(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case DIV:
		if (encoded_inst[3] >= 32 || encoded_inst[3] < 0)
			INST_ALU+=3;
		else
			INST_ALU+=4;
		div(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case SLT:
	case SLTI:
		if (encoded_inst[3] > 32799 || encoded_inst[3] < -32768)
			INST_ALU++;
		INST_ALU++;
		slt(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case LA:
		INST_ALU++;
	case LI: 	
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU++;
		INST_ALU++;
		li(encoded_inst[1], encoded_inst[2]);
		break;
	case SYSCALL:
		INST_OTHER++;
		syscall();
		break;
	case MOVE:
		INST_ALU++;
		move(encoded_inst[1], encoded_inst[2]);
		break;
	case LW:
		INST_MEM++;
		load_word(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case SW:
		INST_MEM++;
		store_word(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case J:
		INST_JUMP++;
		jump(encoded_inst[1]);
		break;
	case JR:
		INST_JUMP++;
		jr(encoded_inst[1]);
		break;
	case JAL:
		INST_JUMP++;
		jal(encoded_inst[1]);
		break;
	case BEQ:
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU++;
		if (encoded_inst[2] >= 32 || encoded_inst[2] < 0)
			INST_ALU++;
		INST_BRANCH++;
		beq(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case BNE:
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU++;
		if (encoded_inst[2] >= 32 || encoded_inst[2] < 0)
			INST_ALU++;
		INST_BRANCH++;
		bne(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case BLT:
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU+=2;
		INST_ALU++;
		INST_BRANCH++;
		blt(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case BLE:
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU++;
		if (encoded_inst[2] >= 32 || encoded_inst[2] < 0)
			INST_ALU++;
		INST_ALU++;
		INST_BRANCH++;
		ble(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case BGT:
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU++;
		if (encoded_inst[2] >= 32 || encoded_inst[2] < 0)
			INST_ALU++;
		INST_ALU++;
		INST_BRANCH++;
		bgt(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	case BGE:
		if (encoded_inst[2] >= 32799 || encoded_inst[2] < -32768)
			INST_ALU+=2;
		INST_ALU++;
		INST_BRANCH++;
		bge(encoded_inst[1], encoded_inst[2], encoded_inst[3]);
		break;
	default:	
		INST_OTHER++;
		cout << ">>> Unknown instruction" << endl;
		pc++;
		//exit(3);			// Exit code 3 => unknown instruction
	}
	return;
}


int label_pos(char *name)
{
	int i;

	for (i = 0; i <= label_num; i++)
	{
		if (labels.label[i].name == name)
			return i;
	}
	labels.label[label_num].name = name;
	labels.label[label_num].inst_num = -1;
	return label_num++;
}


void execute(int fin)
{
	pc = 0;
	for (int i = 0; i <= label_num; i++)
	{
		if (labels.label[i].name == entry)
			pc = labels.label[i].inst_num;
	}
	reg_file[28].val = 0x10008000;
	reg_file[29].val = 0x7fffeffc;
				// Starts with the program totaler at zero
	while (pc < fin)
	{
		decode(im->mem[pc].cod);
	}
	cout << endl;
	cout << "Program Dropped From Bottom..." << endl;
}

int first_char(char*line)
{
	int i;
	for (i = 0; (line[i] == 32 || line[i] == 9) && line[i] != '\x0'; i++);	// '\t'=9, 32 => <space>
	if (line[i] == 10)
		return -1;
	else
		return i;
}

int read_file(FILE*file)
{
	char line[100], temp[100];
	string label;
	int i, k, j, line_num, val;
	line_num = i = k = j = 0;

	int data_text = 0;		// 0=> text , 1 => data (data_text is used to identify the segment of text and of data)

	while (!feof(file))
	{
		line_num++;
		fgets(line, 99, file);
		i = first_char(line);
		if (i == -1 || line[i] == '#')
			continue;
		if (line[i] == '.')
		{
			i++;
			for (j = 0; line[i] != 32 && line[i] != '\x0' && line[i] != 10 && line[i] != 9 && line[i] != '\n'; i++, j++)
			{
				temp[j] = line[i];

			}
			temp[j] = '\x0';
			if (!strcmp("data", temp))
				data_text = 1;
			else if (!strcmp("text", temp))
				data_text = 0;
			else if (!strcmp("globl", temp)) 
			{
				for (; line[i] == 32 || line[i] == ':'; i++, j++);
				for (j = 0; line[i] != '#' && line[i] != '\x0' && line[i] != '\n'; i++, j++) {
					label += line[i];
					temp[j] = line[i];
				}
				entry = label;
			}
			else
			{
				fprintf(stderr, "Syntax error at line number %d", line_num);
				exit(1);
			}

			continue;
		}

		if (data_text == 0)
		{
			// Create a copy of the part of the string containing the instruction

			for (j = 0; line[i] != '#' && line[i] != '\x0' && line[i] != '\n'; i++, j++) {
				label += line[i]; 
				temp[j] = line[i];
			}
			temp[j] = '\x0';
			int coded[5];
			encode(temp, coded, k);
			label.clear();
			if (coded[0])
			{
				load_instruct_mem(k, coded);
				k++;
			}
		}

		else if (data_text == 1)
		{
			string text;
			val = 0;
			for (j = 0; line[i] != '#' && line[i] != '\x0' && line[i] != '\n' && line[i] != 32 && line[i] != ':'; i++, j++)
			{
				label += line[i];
				temp[j] = line[i];
			}		
			temp[j] = '\x0';
			for (; line[i] == 32 || line[i] == ':' || line[i] == '.'; i++, j++);		// To read past the colon and spaces	
			for (; ((line[i] >= 'a' && line[i] <= 'z') || line[i] == '"' || line[i] == ' ') && line[i] != '\x0'; i++);	// To read till the end of the next word (which is 'word')

			for (j = 0; line[i] != '"' && line[i] != '\x0'; i++, j++)
			{
				text += line[i];
			}
			strings[total++].insert(map<string, string>::value_type(label, text));
			text.clear();
			label.clear();
		}
	}
	return k;
}



void add(int dest, int reg1, int reg2)
{
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = a + b;
	pc++;
	return;
}


void sub(int dest, int reg1, int reg2)
{
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = a - b;
	pc++;
	return;
}

void and_(int dest, int reg1, int reg2)
{
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = a & b;
	pc++;
	return;
}



void or_(int dest, int reg1, int reg2)
{
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = a | b;
	pc++;
	return;
}

void slt(int dest, int reg1, int reg2)
{
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = (a<b) ? 1 : 0;
	pc++;
	return;
}

void mul(int dest, int reg1, int reg2) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = a * b;
	pc++;
	return;
}

void div(int dest, int reg1, int reg2) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2>=0) ? reg_file[reg2].val : (reg2>=32) ?reg2-32:reg2;
	reg_file[dest].val = a / b;
	pc++;
	return;
}

void sll(int dest, int reg1, int reg2) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	reg_file[dest].val = a << b;
	pc++;
	return;
}

void li(int dest, int val)
{
	reg_file[dest].val = val;
	pc++;
	return;
}


void move(int dest, int src)
{
	reg_file[dest].val = reg_file[src].val;
	pc++;
	return;
}

void load_word(int dest, int addr, int offset)
{
	if (offset > 0)
		offset -= 32;
	if ((reg_file[addr].val + offset) % 4)
		cout << "Load Word Not Aligned to 4KB" << endl;
	if (reg_file[addr].val + offset < 0x10010000 || reg_file[addr].val + offset > 0x10040000) {
		cout << "Access To Illegal Memory Address " << hex << reg_file[addr].val + offset << endl;
		printPosition();
	}
	if (dm.find((reg_file[addr].val + offset) >> 2) != dm.end())
		reg_file[dest].val = dm[(reg_file[addr].val + offset) >> 2];
	else {
		reg_file[dest].val = 0;
		cout << "Accessed Uninitialized Memory Area " << reg_file[addr].val + offset << endl;
	}
	pc++;
	return;
}

void store_word(int dest, int addr, int offset)
{
	if (offset > 0)
		offset -= 32;
	if ((reg_file[addr].val + offset) % 4)
		cout << "Store Word Not Aligned to 4KB" << endl;
	if (reg_file[addr].val + offset < 0x10010000 || reg_file[addr].val + offset > 0x10040000) {
		cout << "Access To Illegal Memory Address " << hex << reg_file[addr].val + offset << endl;
		printPosition();
	}
	dm[(reg_file[addr].val + offset)>>2] = reg_file[dest].val;
	pc++;
	return;
}
void jump(int pc_dest)
{
	pc = labels.label[pc_dest].inst_num;
	return;
}
void jr(int pc_dest) {
	pc = reg_file[pc_dest].val;
	return;
}
void jal(int pc_dest) {
	reg_file[31].val = pc + 1;
	pc = labels.label[pc_dest].inst_num;
	return;
}


void beq(int reg1, int reg2, int pc_dest)
{
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	if (a == b)
		pc = labels.label[pc_dest].inst_num;
	else
		pc++;
	return;
}

void bne(int reg1, int reg2, int pc_dest) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	if (a != b)
		pc = labels.label[pc_dest].inst_num;
	else
		pc++;
	return;
}

void blt(int reg1, int reg2, int pc_dest) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	if (a < b)
		pc = labels.label[pc_dest].inst_num;
	else
		pc++;
	return;
}
void ble(int reg1, int reg2, int pc_dest) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	if (a <= b)
		pc = labels.label[pc_dest].inst_num;
	else
		pc++;
	return;
}
void bgt(int reg1, int reg2, int pc_dest) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	if (a > b)
		pc = labels.label[pc_dest].inst_num;
	else
		pc++;
	return;
}
void bge(int reg1, int reg2, int pc_dest) {
	int a = (reg1<32) ? reg_file[reg1].val : reg1 - 32;
	int b = (reg2<32 && reg2 >= 0) ? reg_file[reg2].val : (reg2 >= 32) ? reg2 - 32 : reg2;
	if (a >= b)
		pc = labels.label[pc_dest].inst_num;
	else
		pc++;
	return;
}

string CancelEscape(string str) {
	for (string::iterator i = str.begin(); i != str.end() - 1; i++) {
		if (*i == '\\' && *(i + 1) == '\\') {
			str.erase(i + 1);
		}
	}
	return str;
}

void syscall()
{
	if (reg_file[2].val == 1)
	{
		cout << reg_file[4].val;
	}
	else if (reg_file[2].val == 5)
	{
		int temp;
		if (cin >> temp)
			reg_file[2].val = temp;
		else {
			reg_file[2].val = 0;
			cout << "Invalid Input Number..." << endl;
		}
	}
	else if (reg_file[2].val == 11) {	// Char
		cout << (char)reg_file[4].val;
	}
	else if (reg_file[2].val == 4) {	// String
		if (strings[reg_file[4].val].size() == 0) {
			cout << "Unrecognized Identider " << reg_file[4].val << endl;
			pc++;
			return;
		}
		cout << CancelEscape(strings[reg_file[4].val].begin()->second);
	}
	else if (reg_file[2].val == 12)
	{
		char temp;
		if (cin >> temp)
			reg_file[2].val = (int)temp;
		else {
			reg_file[2].val = (int)'0';
			cout << "Invalid Input Char..." << endl;
		}
	}
	else if (reg_file[2].val == 10)
	{
		exit(0);
	}
	pc++;
	return;
}


void init_reg_file()
{
	reg_file[0].alt_name = "zero";
	reg_file[1].alt_name = "at";
	reg_file[2].alt_name = "v0";
	reg_file[3].alt_name = "v1";
	reg_file[4].alt_name = "a0";
	reg_file[5].alt_name = "a1";
	reg_file[6].alt_name = "a2";
	reg_file[7].alt_name = "a3";
	reg_file[8].alt_name = "t0";
	reg_file[9].alt_name = "t1";
	reg_file[10].alt_name = "t2";
	reg_file[11].alt_name = "t3";
	reg_file[12].alt_name = "t4";
	reg_file[13].alt_name = "t5";
	reg_file[14].alt_name = "t6";
	reg_file[15].alt_name = "t7";
	reg_file[16].alt_name = "s0";
	reg_file[17].alt_name = "s1";
	reg_file[18].alt_name = "s2";
	reg_file[19].alt_name = "s3";
	reg_file[20].alt_name = "s4";
	reg_file[21].alt_name = "s5";
	reg_file[22].alt_name = "s6";
	reg_file[23].alt_name = "s7";
	reg_file[24].alt_name = "t8";
	reg_file[25].alt_name = "t9";
	reg_file[26].alt_name = "k0";
	reg_file[27].alt_name = "k1";
	reg_file[28].alt_name = "gp";
	reg_file[29].alt_name = "sp";
	reg_file[30].alt_name = "fp";
	reg_file[31].alt_name = "ra";
	return;
}

int reg_num(char*alt_name)
{
	int i;
	i = strlen(alt_name);
	if (i == 1)
		return alt_name[0] - '0';
	for (i = 0; i<32; i++)
	{
		if (reg_file[i].alt_name == alt_name)
			break;
	}

	if (i != 32)
		return i;
	if (!strcmp(alt_name, "s8"))
		return 30;
	else
	{
		printf("Syntax error. %s : no such register", alt_name);
		printPosition();
		exit(1);				// Error of register name yields an exit code 1
	}
}

int main(int argc, char*args[])
{
	init_reg_file();		// Initialize the register file
	label_num = 0;
	FILE *f;
	fopen_s(&f, "num.asm", "r");
	int len = read_file(f);	// len stores the largest possible value of pc.
	fclose(f);
	execute(len);
	cout << "--------------------------------" << endl;
	cout << "--- ALU       | " << INST_ALU << endl;
	cout << "--- JUMP      | " << INST_JUMP << endl;
	cout << "--- BRANCH    | " << INST_BRANCH << endl;
	cout << "--- MEMORY    | " << INST_MEM << endl;
	cout << "--- OTHER     | " << INST_OTHER << endl;
	cout << "--- TOTAL     | " << INST_ALU + INST_JUMP + INST_BRANCH + INST_MEM + INST_OTHER << endl;
	cout << ">>> Benchmark | " << runBenchmark() << endl;
	delete [] im;
	return 0;
}
