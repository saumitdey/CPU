/*
 * Memory.h
 *
 *  Created on: Feb 12, 2015
 *      Author: sdey
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stddef.h>

class Memory {
public:
	Memory();
	virtual ~Memory();

	char* memRead(size_t byteOffset, size_t sizeInByte);
	void memWrite (size_t byteOffset, char* content_binaryString);
	void memDump(int startLocation, int range);
	void memReset();

	// size in bytes
	static const int MEM_SIZE = 4*500+3;

	static const int BootStrap_Base = 4*0;
	static const int BootStrap_Limit = 4*99;

	static const int Instruction_Base = 4*100;
	static const int Instruction_Limit = 4*199;

	static const int Data_Base = 4*200;
	static const int Data_Limit = 4*499;

private:
	int *content;
};

#endif /* MEMORY_H_ */
