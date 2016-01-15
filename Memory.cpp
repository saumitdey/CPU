/*
 * Memory.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: sdey
 */

#include "Memory.h"
#include "ToolBox.h"
using namespace std;
/*
 * memory content stored as integer
 * when presenting them, converting them into binary
 */
Memory::Memory() {
	//each integer represents one byte - byte addressing (decimal range: -128 ~ +127)
	content = new int[MEM_SIZE];
	for(int i=0;i<MEM_SIZE;i++)	content[i]=0;
}

Memory::~Memory() {
	delete[] content;
}

/*
 * read a block of 4 bytes from memory
 */
char* Memory::memRead(size_t byteOffset, size_t sizeInByte){
	//int *ByteMemBlock = new int[sizeInByte];
	char* temp=NULL;
	char* finalBinaryString = new char[33];

	for(int i=0; i<sizeInByte; i++){
		temp = ToolBox::convertInteger2BinaryString(content[byteOffset+i], 8);
		strcat(finalBinaryString, temp);
	}

	return finalBinaryString;
}
/*
 * write a block of 4 bytes to memory
 */
void Memory::memWrite(size_t byteOffset, char* content_binaryString){

	int equivalentDecimal = ToolBox::convertBinaryString2Integer(content_binaryString);
	int *fourByteMemBlock = ToolBox::parseRegByteSegment(equivalentDecimal);

	for(int i=0; i<4; i++){
		content[byteOffset+i] = fourByteMemBlock[i];
	}
}


void Memory::memDump(int startLocation, int blockRange){
	for(int i=0; i<blockRange; i++){
		char* temp = memRead(startLocation, 4);

		ToolBox::printCharArry(temp);
		cout<<"	Row("<<startLocation/4<<")/"<<"StartByte("<<startLocation<<" )"<<endl;
		startLocation +=4;
	}
}

void Memory::memReset(){
	for(int i=0;i<MEM_SIZE;i++)	content[i]=0;
}
