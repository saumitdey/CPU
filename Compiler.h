/*
 * Compiler.h
 *
 *  Created on: Feb 13, 2015
 *      Author: sdey
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include <regex>
#include <iostream>
#include <string.h>
#include "Register.h"

using namespace std;

class Compiler {
public:
	Compiler();
	virtual ~Compiler();
	/*
	 * Addressing Mode: LW/SW
	 * 	|~~~ 31-24 ~~~|~~~ 23-20 ~~~|~~~ 19-16 ~~~|~~~ 15-0 ~~~|
	 * 		opcode			Rs			  Rt		   Imm
	 * 		8-bit		   4-bit		 4-bit		  16-bit
	 *
	 * 	lw = "00000000"
	 * 	st = "00000001"
	 * 	Rs = "0000"
	 * 	Rt = "0001"
	 * 	Imm = binary-equivalent decimal (left padding to 16 bit)
	 *
	 * 	supported instructions
	 * 		addi $rt, $rs, immed
	 * 		lw  $rt, offset($rs)
	 * 		sw  $rt, offset($rs)
	 */
	const static int OPCODE_SPACE = 8;
	const static int Regisger_SPACE = 4;
	const static int IMM_SPACE = 16;

	const static int OPCODE_SW = 0;		//00000000
	const static int OPCODE_LW = 1; 	//00000001
	const static int OPCODE_ADDI = 2;	//00000010


	static char* compileInstrToBinarySting(string instructon);
	static int* extractBinaryInstruction(char* binaryInstruction);

	//static int* loadInstructionFromMemory(int programCounterValue);
	//static void storeInstructionIntoMemory(string instruction, int memoryLocation);

	static void printExtractedInstruction(int* instCompo);

private:
	int* instSegment[4];		//instruction segment

};

#endif /* COMPILER_H_ */
