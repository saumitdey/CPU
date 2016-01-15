/*
 * ToolBox.h
 *
 *  Created on: Feb 12, 2015
 *      Author: sdey
 */

#ifndef TOOLBOX_H_
#define TOOLBOX_H_

#include <iostream>
#include <stddef.h>
#include <cmath>
#include <fstream>
#include "Compiler.h"
#include "Memory.h"
#include "Register.h"
using namespace std;


class ToolBox {

public:
	ToolBox();
	virtual ~ToolBox();

	// Constants
	static const int MAX_BINARY_SIZE = 32;
	static const int SIZE_OF_BYTE = 8;

	// basic integer to binary conversion
	static char* convertInteger2BinaryString(int myInt, int binaryStringSize);
	static int convertBinaryString2Integer(char* binaryString);

	// register to memory mapping
	static int* parseRegByteSegment(int regValue);
	static char** fourSegmentBinaryString(char* binaryString, int segSize1, int segSize2, int segSize3, int segSize4);
	static int parseRamByteAggretage(int *fourByteRamBlock);

	static char* binaryStringLeftPadding(char* binaryString, int finalSize);
	static int twosComplement(char* binaryString);


	static void printCharArry(char * charArry);
	static int getStringSize(char *string);

	static bool loadProgram(string path, Memory* myMem, Register* myReg, int loadLocation);
	static void loadInstructionsIntoMemory(string instructon, int writeLocation, Memory* myMem, Register* myReg);
	static void executeProgram(Memory* myMem, Register* myReg);
	static void execute(char* instruction, Memory* myMem, Register* myReg);

};

#endif /* TOOLBOX_H_ */
