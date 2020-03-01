//COSC 130
//Shravan Pinni
//3/14/19
//Extra Credit Lab
//Worked with

#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

struct Codes{
	int opcode;
	int func3;
	int imm;
	int rs1;
	int rd;
	int shamt;
	int rs2;
	int binary;

};


int main(int argc, char* argv[]){
	
	int outputT = 0;
	FILE* fout = fopen(argv[2],"w");
	FILE* fin;

//Checks if the number of arguments is valid
	if(argc < 3 || argc > 4){
		printf("Invalid number of arguments");
		return -1;
	}


	if(strcmp(argv[3], "x:") == 0)
		outputT = 1;
	if(strcmp(argv[3], "x") == 0)
		outputT = 1;

	if(strcmp(argv[2],"-") == 0)
		fout = stdout;
	


//Opens file and checks if it actually opens
	fin = fopen(argv[1], "rb");

	if(fin == nullptr){
		printf("Incorrect file");
		return -1;

	}


//array for the ABIs that correlate to the xregisters
const char* ABI[32] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1","a0", "a1", "a2", "a3", "a4", "a5", "a6",						"a7","s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

//sets seek to end to find total bytes
	fseek(fin, 0, SEEK_END);
	int length = ftell(fin);
	int size = length / 4;

//sets seek back to 0
	fseek(fin,0,SEEK_SET);

//declaring a pointer of the Code struct
	Codes *ptr = new Codes[size];

	for(int i = 0;i < size;i++){
		fread(&ptr[i].binary, 1, 4, fin);
	}

	fclose(fin);


//Gets opcode for each instruction
	for(int i = 0; i<size;i++){
		ptr[i].opcode = ptr[i].binary & 0x7F;
	}

//for and switch to find instruction and return
	for(int i = 0;i<size;i++){
		switch(ptr[i].opcode){
//case for liu
			case 55:
				ptr[i].rd = ptr[i].binary & 0xF80;
				ptr[i].rd = ptr[i].rd >> 7;
				
				ptr[i].imm = ptr[i].binary & 0xFFFFF000;
				
				if(outputT == 0)
					fprintf(fout, "     lui   %s %d      //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm, ptr[i].binary);
				else
					fprintf(fout, "     lui   x%d %d     //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].binary);
				
			break;
//case for jalr
			case 103:
				ptr[i].rd = ptr[i].binary & 0xF80;
				ptr[i].rd = ptr[i].rd >> 7;
				
				ptr[i].imm = ptr[i].binary & 0xFFF00000;
				ptr[i].imm = ptr[i].imm >> 20;

				ptr[i].rs1 = ptr[i].binary >> 15;
				ptr[i].rs1 = ptr[i].rs1& 0x1f;
				
				if(outputT == 0)
					fprintf(fout, "     jalr   %s   %s   %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1], ptr[i].imm, ptr[i].binary);
				else
					fprintf(fout, "     jalr   x%d  x%d  %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].imm, ptr[i].binary);


			break;
//case for jal
			case 111:

			//takes out rd
				ptr[i].rd = ptr[i].binary & 0xF80;
				ptr[i].rd = ptr[i].rd >> 7;
			//takes out the 20 part of imm
				ptr[i].func3 = ptr[i].binary & 0xFFFFF000;
				ptr[i].func3 = ptr[i].binary >> 31;
			//takes out the 10-1 part of imm
				ptr[i].rs1 = ptr[i].binary >> 20;
				ptr[i].rs1 = ptr[i].rs1 & 0x1;
			//takes out the 11 part of imm
				ptr[i].rs2 = ptr[i].binary >> 21;
				ptr[i].rs2 = ptr[i].rs2 & 0x3FF;
			//takes out the 19-12 part of imm
				ptr[i].shamt = ptr[i].binary >> 12;
				ptr[i].shamt = ptr[i].shamt & 0xff;

				ptr[i].imm = ptr[i].func3 << 20 | ptr[i].shamt << 12 | ptr[i].rs1 << 11 | ptr[i].rs2 << 1;

				if(outputT == 0)
					fprintf(fout, "     jal   %s %d             //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm, ptr[i].binary);
				else
					fprintf(fout, "     jal   x%d %d            //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].binary);
	
				break;

//case for load instructions
			case 3:
				ptr[i].func3 = ptr[i].binary & 0x7000;
				ptr[i].func3 = ptr[i].func3 >> 12;

													
				ptr[i].rd = ptr[i].binary & 0xF80;
				ptr[i].rd = ptr[i].rd >> 7;
			
				ptr[i].imm = ptr[i].binary & 0xFFF00000;
				ptr[i].imm = ptr[i].imm >> 20;

				ptr[i].rs1 = ptr[i].binary >> 15;
				ptr[i].rs1 = ptr[i].rs1& 0x1f;
			
				if(ptr[i].func3 == 0){

					if(outputT == 0)
						fprintf(fout, "     lb   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     lb   x%d  %d(x%d)        //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);

				}
			else if(ptr[i].func3 == 1){

					if(outputT == 0)
						fprintf(fout, "     lh   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     lh   x%d  %d(x%d)        //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);

				}
			else if(ptr[i].func3 == 2){

					if(outputT == 0)
						fprintf(fout, "     lw   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     lw   x%d  %d(x%d)        //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);

				}

			else if(ptr[i].func3 == 6 ){

					if(outputT == 0)
						fprintf(fout, "     lwu   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     lwu   x%d  %d(x%d)        //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);

				}

			else{

				if(outputT == 0)
					fprintf(fout, "     ld   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rd], ptr[i].imm,
							ABI[ptr[i].rs1],ptr[i].binary);
				else
					fprintf(fout, "     ld   x%d  %d(x%d)        //0x%08x\n", ptr[i].rd, ptr[i].imm, ptr[i].rs1,
						 ptr[i].binary);
				}

			break;

//case for store instructions
			case 35:

				ptr[i].func3 = ptr[i].binary & 0x7000;
				ptr[i].func3 = ptr[i].func3 >> 12;
//imm4-0
				ptr[i].shamt = ptr[i].binary & 0xF80;
				ptr[i].shamt = ptr[i].shamt >> 7; 
//imm11-5
				ptr[i].rd = ptr[i].binary & 0xFE000000;
				ptr[i].rd = ptr[i].rd >> 25;
//rs1
				ptr[i].rs1 = ptr[i].binary >> 15;
				ptr[i].rs1 = ptr[i].rs1 & 0x1f;
//rs2
				ptr[i].rs2 = ptr[i].binary >> 20;
				ptr[i].rs2 = ptr[i].rs2 & 0x1f;

				ptr[i].imm = ptr[i].rd << 5 | ptr[i].shamt;

				if(ptr[i].func3 == 0){

					if(outputT == 0)
						fprintf(fout, "     sb   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rs2], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     sb   x%d  %d(x%d)        //0x%08x\n", ptr[i].rs2, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);
				}

				else if(ptr[i].func3 == 1){

					if(outputT == 0)
						fprintf(fout, "     sh   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rs2], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     sh   x%d  %d(x%d)        //0x%08x\n", ptr[i].rs2, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);
				}
					
				else if(ptr[i].func3 == 2){

					if(outputT == 0)
						fprintf(fout, "     sw   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rs2], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else
						fprintf(fout, "     sw   x%d  %d(x%d)        //0x%08x\n", ptr[i].rs2, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);
				}
				else{
					if(outputT == 0)
						fprintf(fout, "     sd   %s  %d( %s)        //0x%08x\n", ABI[ptr[i].rs2], ptr[i].imm,
								ABI[ptr[i].rs1],ptr[i].binary);
					else{
						fprintf(fout, "     sd   x%d  %d(x%d)        //0x%08x\n", ptr[i].rs2, ptr[i].imm, ptr[i].rs1,
								 ptr[i].binary);
					}
					}
			break;

			case 19:
				ptr[i].func3 = ptr[i].binary & 0x7000;
				ptr[i].func3 = ptr[i].func3 >> 12;
													
				ptr[i].rd = ptr[i].binary & 0xF80;
				ptr[i].rd = ptr[i].rd >> 7;
				
				ptr[i].rs1 = ptr[i].binary >> 15;
				ptr[i].rs1 = ptr[i].rs1 & 0x1f;

				if(ptr[i].func3 == 0){
					ptr[i].imm = ptr[i].binary & 0xFFF00000;
					ptr[i].imm = ptr[i].imm >> 20;


					if(outputT == 0){
						fprintf(fout, "     addi   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].imm, ptr[i].binary);
					}
					else{
						fprintf(fout, "     addi   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].imm,
							 ptr[i].binary);
					}
				}
				else if(ptr[i].func3 == 4){
					ptr[i].imm = ptr[i].binary & 0xFFF00000;
					ptr[i].imm = ptr[i].imm >> 20;


					if(outputT == 0){
						fprintf(fout, "     xori   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].imm, ptr[i].binary);
					}
					else{
						fprintf(fout, "     xori   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].imm,
							 ptr[i].binary);
					}
				}
				else if(ptr[i].func3 == 6){
					ptr[i].imm = ptr[i].binary & 0xFFF00000;
					ptr[i].imm = ptr[i].imm >> 20;

					if(outputT == 0){
						fprintf(fout, "     xor   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].imm, ptr[i].binary);
					}
					else{
						fprintf(fout, "     xor   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].imm,
							 ptr[i].binary);
					}
			}
			else if(ptr[i].func3 == 7){
					ptr[i].imm = ptr[i].binary & 0xFFF00000;
					ptr[i].imm = ptr[i].imm >> 20;

					if(outputT == 0){
						fprintf(fout, "     andi   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].imm, ptr[i].binary);
					}
					else{
						fprintf(fout, "     andi   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].imm,
							 ptr[i].binary);
					}
				}
			else if(ptr[i].func3 == 1){
					ptr[i].shamt = ptr[i].binary & 0x3f00000;
					ptr[i].shamt = ptr[i].shamt >> 20;
			
					if(outputT == 0){
						fprintf(fout, "     slli   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].shamt, ptr[i].binary);
					}
					else{
						fprintf(fout, "     slli   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].shamt,
							 ptr[i].binary);
					}
			}
			else{
				ptr[i].imm = ptr[i].binary >> 26;

				ptr[i].shamt = ptr[i].binary & 0x3f00000;
				ptr[i].shamt = ptr[i].shamt >> 20;

				if(ptr[i].imm == 0){

					if(outputT == 0){
						fprintf(fout, "     srli   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].shamt, ptr[i].binary);
					}
					else{
						fprintf(fout, "     srli   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].shamt,
							 ptr[i].binary);
					}
				}
				else{	
					if(outputT == 0){
						fprintf(fout, "     srai   %s  %s, %d        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
								ptr[i].shamt, ptr[i].binary);
					}
					else{
						fprintf(fout, "     srai   x%d x%d, %d        //0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].shamt,
							 ptr[i].binary);
					}
				}
	

			} 
			break;

			case 51:
				ptr[i].func3 = ptr[i].binary & 0x7000;
				ptr[i].func3 = ptr[i].func3 >> 12;

				ptr[i].imm = ptr[i].binary >> 25;
	
				ptr[i].rd = ptr[i].binary & 0xF80;
				ptr[i].rd = ptr[i].rd >> 7;
				
				ptr[i].rs1 = ptr[i].binary >> 15;
				ptr[i].rs1 = ptr[i].rs1 & 0x1f;

				ptr[i].rs2 = ptr[i].binary >> 20;
				ptr[i].rs2 = ptr[i].rs2 & 0x1f;
				
				if(ptr[i].func3 == 0 && ptr[i].imm == 0){
				if(outputT == 0){
					fprintf(fout, "     add   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     add   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}
				
				else if(ptr[i].func3 == 0 && ptr[i].imm == 32){
				if(outputT == 0){
					fprintf(fout, "     sub   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     sub   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}

				else if(ptr[i].func3 == 1 && ptr[i].imm == 0){
				if(outputT == 0){
					fprintf(fout, "     sll   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     sll   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}

				else if(ptr[i].func3 == 4 && ptr[i].imm == 0){
				if(outputT == 0){
					fprintf(fout, "     xor   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     xor   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}

				else if(ptr[i].func3 == 5 && ptr[i].imm == 0){
				if(outputT == 0){
					fprintf(fout, "     srl   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     srl   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}

				else if(ptr[i].func3 == 5 && ptr[i].imm == 32){
				if(outputT == 0){
					fprintf(fout, "     sra   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     sra   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}

				else if(ptr[i].func3 == 6 && ptr[i].imm == 0){
				if(outputT == 0){
					fprintf(fout, "     or   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     or   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}

				else {
				if(outputT == 0){
					fprintf(fout, "     and   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     and   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
				}
			break;

			case 27:	
				ptr[i].func3 = ptr[i].binary & 0x7000;
				ptr[i].func3 = ptr[i].func3 >> 12;

				if(outputT == 0){
					fprintf(fout, "     and   %s  %s, %s        //0x%08x\n", ABI[ptr[i].rd], ABI[ptr[i].rs1],
							ABI[ptr[i].rs2], ptr[i].binary);
					}
				else{
					fprintf(fout, "     and   x%d x%d, x%d		//0x%08x\n", ptr[i].rd, ptr[i].rs1, ptr[i].rs2, ptr[i].binary);
					}
			break;

			default:

				fprintf(fout, "     inv   invalid	//0x%08x\n",  ptr[i].binary);

			break;
		}

	}

	

}
