/*
 * Compiler.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: sdey
 */

#include "Compiler.h"
#include "ToolBox.h"
#include "Memory.h"

Compiler::Compiler() {
	// TODO Auto-generated constructor stub

}

Compiler::~Compiler() {
	// TODO Auto-generated destructor stub
}

//void Compiler::storeInstructionIntoMemory(string instruction, int memoryLocation){
//	char* binaryInstruction = compileInstrToBinarySting(instruction);
//}



char* Compiler::compileInstrToBinarySting(string instruction){

	char* buff = new char[33];	buff[32]='\0';

	regex lwSwFamily_pattern("[ ]*([a-zA-Z]*)[ ]+\\$([a-zA-Z0-9]+)[ ]*,[ ]*(-?[0-9]+)\\(\\$([a-zA-Z0-9]+)\\)[ ]*");		//lw  $rt, offset($rs)
	regex addiFamily_pattern("[ ]*([a-zA-Z]*)[ ]+\\$([a-zA-Z0-9]+)[ ]*,[ ]*\\$([a-zA-Z0-9]+)[ ]*,[ ]*(-?[0-9]+)[ ]*");		//addi $rt, $rs, immed

	smatch m_lwSw, m_addi;
	bool isLwSwFamily = regex_match(instruction, m_lwSw, lwSwFamily_pattern);
	bool isAddiFamily = regex_match(instruction, m_addi, addiFamily_pattern);

	const char* opCode;		char* b_opCode=NULL;
	int imm;				char* b_imm=NULL;
	const char* regRs;		char* b_regRs=NULL;
	const char* regRt;;		char* b_regRt=NULL;

	if(isLwSwFamily==true){
		opCode = m_lwSw[1].str().c_str();
		regRs = m_lwSw[4].str().c_str();
		regRt = m_lwSw[2].str().c_str();
		imm = stoi(m_lwSw[3]);

		if(strcmp(opCode, "lw")==0){
			b_opCode = ToolBox::convertInteger2BinaryString(Compiler::OPCODE_LW, Compiler::OPCODE_SPACE);
		}else if(strcmp(opCode,"sw")==0){
			b_opCode = ToolBox::convertInteger2BinaryString(Compiler::OPCODE_SW, Compiler::OPCODE_SPACE);
		}else{
			return NULL;
		}

		b_regRs = ToolBox::convertInteger2BinaryString(Register::registerMapper(regRs), Compiler::Regisger_SPACE);
		b_regRt = ToolBox::convertInteger2BinaryString(Register::registerMapper(regRt), Compiler::Regisger_SPACE);
		b_imm = ToolBox::convertInteger2BinaryString(imm, Compiler::IMM_SPACE);


		for(int i=0; i<32; i++){
			if(i<=7){
				buff[i]=b_opCode[i];
			}
			if(i>=8 && i<=11){
				buff[i]=b_regRs[i-8];
			}
			if(i>=12&& i<=15){
				buff[i]=b_regRt[i-12];
			}
			if(i>=16 && i<=31){
				buff[i]=b_imm[i-16];
			}
		}

		return buff;
	}else if(isAddiFamily==true){
		opCode = m_addi[1].str().c_str();
		regRs = m_addi[3].str().c_str();
		regRt = m_addi[2].str().c_str();
		imm = stoi(m_addi[4]);
		if(strcmp(opCode, "addi")==0){
			b_opCode = ToolBox::convertInteger2BinaryString(Compiler::OPCODE_ADDI, Compiler::OPCODE_SPACE);
			b_regRs = ToolBox::convertInteger2BinaryString(Register::registerMapper(regRs), Compiler::Regisger_SPACE);
			b_regRt = ToolBox::convertInteger2BinaryString(Register::registerMapper(regRt), Compiler::Regisger_SPACE);
			b_imm = ToolBox::convertInteger2BinaryString(imm, Compiler::IMM_SPACE);


			for(int i=0; i<32; i++){
				if(i<=7){
					buff[i]=b_opCode[i];
				}
				if(i>=8 && i<=11){
					buff[i]=b_regRs[i-8];
				}
				if(i>=12&& i<=15){
					buff[i]=b_regRt[i-12];
				}
				if(i>=16 && i<=31){
					buff[i]=b_imm[i-16];
				}
			}

			return buff;
		}else{
			return NULL;
		}
	}else{
		return NULL;
	}
}

int* Compiler::extractBinaryInstruction(char* binaryInstruction){
	int* instruction = new int[4];
	char* ptr;
	char opCode[9];	opCode[8]='\0';
		ptr = binaryInstruction;
		strncpy(opCode, ptr, 8);
		instruction[0] = ToolBox::convertBinaryString2Integer(opCode);
		//ToolBox::printCharArry(opCode);
	char regRs[5]; regRs[4]='\0';
		ptr = binaryInstruction+8;
		strncpy(regRs, ptr, 4);
		instruction[1] = ToolBox::convertBinaryString2Integer(regRs);
		//ToolBox::printCharArry(regRs);
	char regRt[5]; regRt[4]='\0';
		ptr = binaryInstruction+12;
		strncpy(regRt, ptr, 4);
		instruction[2] = ToolBox::convertBinaryString2Integer(regRt);
		//ToolBox::printCharArry(regRt);
	char imm[17]; imm[16]='\0';
		ptr = binaryInstruction+16;
		strncpy(imm, ptr, 16);
		instruction[3] = ToolBox::convertBinaryString2Integer(imm);
		//ToolBox::printCharArry(imm);
	return instruction;
}


void Compiler::printExtractedInstruction(int* instCompo){
	for(int i=0; i<4; i++){
		cout<<instCompo[i]<<"~~~";
	}
	cout<<endl;
}


