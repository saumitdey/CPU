/*
 * ToolBox.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: sdey
 */

#include "ToolBox.h"

ToolBox::ToolBox() {
	// TODO Auto-generated constructor stub

}

ToolBox::~ToolBox() {
	// TODO Auto-generated destructor stub
}

/*
 * convert any integer(>=0) into binary string(<=32 bit) -ex "0011011110"
 * return NULL if binaryStringSize cannot hold myInt
 */
char* ToolBox::convertInteger2BinaryString(int myInt, int binaryStringSize){
	char* buf = new char[binaryStringSize+1];
	buf[binaryStringSize] = '\0';
	for(int i=0; i<binaryStringSize; i++){
		buf[i]='0';
	}

	char* headPtr = buf+binaryStringSize;

	if(myInt >= 0){
		for( ; myInt/2!=0; myInt=myInt/2){
			headPtr--;
			if(myInt%2 == 1){
				*headPtr = '1';
			}else{
				*headPtr = '0';
			}
		}
		headPtr--;
		*headPtr= (myInt%2==1?'1':'0');

		if(headPtr<buf){
			return NULL;
		}else{
			return buf;
		}
	}else{
		myInt = myInt*(-1);
		char *temp = convertInteger2BinaryString(myInt, binaryStringSize);
		if(temp==NULL){
			return NULL;
		}else{
			twosComplement(temp);
			return temp;
		}
	}
}

/*
 * convert any unsigned binary string (ex "0011011110", <=32bit) into decimal with equivalent value
 * do not need to specify the binaryStringSize because we can determine the +/- value by looking at the MSB of the binary string
 */
int ToolBox::convertBinaryString2Integer(char *binaryString){
	int value=0;
	int size=getStringSize(binaryString);
	char *ptr = binaryString;

	if(binaryString[0]=='0'){
		for( ; *binaryString!='\0'; binaryString++){
			if(*binaryString == '1'){
				value = value + 1*pow(2,size-1);
			}
			size--;
		}
		return value;
	}else{
		int carry = twosComplement(binaryString);
		return convertBinaryString2Integer(binaryString)*(-1);
	}
}

/*
 * left padding with binary string with '0' until reach size of 32-bit
 */
char* ToolBox::binaryStringLeftPadding(char *binaryString, int finalSize){
	char* newString = new char[finalSize+1];
	newString[finalSize] = '\0';

	char zeroORone = binaryString[0];

	int length = getStringSize(binaryString);
	if(finalSize<length){
		return NULL;
	}else{
		char* ptr = binaryString;

		for(int i=0; i<finalSize; i++){
			if(i<(finalSize-length)){
				newString[i]=zeroORone;
			}else{
				newString[i] = *ptr;
				ptr++;
			}
		}
		return newString;
	}
}

/*
 * divide register integer value into 4x8-bit binary segment and represent each segment as integer for memory storage
 */
int* ToolBox::parseRegByteSegment(int regValue){

	char *regBitString = convertInteger2BinaryString(regValue,32);

	int* memBlock = new int[4];

	char *buffer = new char[9];
	buffer[0] = '\0';

	for(int byteBlock=0; byteBlock<4; byteBlock++){
		for(int bit=byteBlock*8; bit<byteBlock*8+8 ;bit++){
			buffer[bit-byteBlock*8] = regBitString[bit];
		}
		memBlock[byteBlock] = convertBinaryString2Integer(buffer);
	}
	return memBlock;
}

char** ToolBox::fourSegmentBinaryString(char* binaryString, int seg1Size, int seg2Size, int seg3Size, int seg4Size){
	int size =getStringSize(binaryString);
	if(size != seg1Size+seg2Size+seg3Size+seg4Size){
		return NULL;
	}else{
		char** temp = new char*[4];

		char* ptr=binaryString;
		char* seg1 = new char[seg1Size+1];	seg1[seg1Size]='\0';
			int seg1_left = 0; int seg1_right = seg1_left+seg1Size-1;
			strncpy(seg1, ptr, seg1Size);
			ptr += seg1Size;
			temp[0]=seg1;

		char* seg2 = new char[seg2Size+1];  seg2[seg2Size]='\0';
			int seg2_left = seg1_right+1; int seg2_right = seg2_left+seg2Size-1;
			strncpy(seg2, ptr, seg2Size);
			ptr +=seg2Size;
			temp[1]=seg2;

		char* seg3 = new char[seg3Size+1]; 	seg3[seg3Size]='\0';
			int seg3_left = seg2_right+1; int seg3_right = seg3_left+seg3Size-1;
			strncpy(seg3, ptr, seg3Size);
			ptr += seg3Size;
			temp[2]=seg3;

		char* seg4 = new char[seg4Size+1];	seg4[seg4Size]='\0';
			int seg4_left = seg3_right+1; int seg4_right = seg4_left+seg4Size-1;
			strncpy(seg4, ptr, seg4Size);
			temp[3]=seg4;

		return temp;
	}

}



/*
 * aggregate a four byte ram block and evaluate to an integer
 */
int ToolBox::parseRamByteAggretage(int *fourByteRamBlock){
	char *str1 = convertInteger2BinaryString(fourByteRamBlock[0], 8);
	char *str2 = convertInteger2BinaryString(fourByteRamBlock[1], 8);
	char *str3 = convertInteger2BinaryString(fourByteRamBlock[2], 8);
	char *str4 = convertInteger2BinaryString(fourByteRamBlock[3], 8);

	str1 = strcat(str1, str2);
	str1 = strcat(str1, str3);
	str1 = strcat(str1, str4);

	return convertBinaryString2Integer(str1);
}


int ToolBox::twosComplement(char *binaryString){
	int size = getStringSize(binaryString);
	// invert all the bits
	for(int i=0; i<size; i++){
		if(binaryString[i]=='1'){
			binaryString[i]='0';
		}else{
			binaryString[i]='1';
		}
	}

	// add 1
	for(int i=size-1; i>=0; i--){
		if(binaryString[i]=='0'){
			binaryString[i]='1';
			return 0;
		}else{
			binaryString[i]='0';
		}
	}
	return 1;
}

bool ToolBox::loadProgram(string path, Memory* myMem, Register* myReg, int loadLocation){

	if(loadLocation<Memory::Instruction_Base || loadLocation>Memory::Instruction_Limit){
		cout<< "Segmentation Fault: Unable to load program to memory"<<endl;
		return false;
	}else{
		ifstream inFile(path);
		string line;

		myReg->setValue(Register::Reg_ProgCntr, loadLocation);
		myReg->setValue(Register::Reg_ProgBase, loadLocation);
		myReg->setValue(Register::Reg_ProgLimit, loadLocation);

		while(getline(inFile, line)){
			if(myReg->getValue(Register::Reg_ProgLimit) <= (Memory::Instruction_Base+Memory::Instruction_Limit)){
				ToolBox::loadInstructionsIntoMemory(line, myReg->getValue(Register::Reg_ProgLimit), myMem, myReg);
				myReg->setValue(Register::Reg_ProgLimit, myReg->getValue(Register::Reg_ProgLimit)+4);
			}else{
				cout<<"Segmentation Fault: instructions exceed designated memory segment"<<endl;
				myReg->reset();
				return false;
			}
		}
		cout<<"Loading Instructions Success"<<endl;
		return true;
	}
}
void ToolBox::loadInstructionsIntoMemory(string instructon, int writeLocation, Memory* myMem, Register* myReg){
	char* binaryInstructionString = Compiler::compileInstrToBinarySting(instructon);
	myMem->memWrite(writeLocation, binaryInstructionString);
	myReg->setValue(Register::Reg_MAR, writeLocation);
	myReg->setValue(Register::Reg_MDR, ToolBox::convertBinaryString2Integer(binaryInstructionString));
	cout<<"=== Compile and Load Instruction: "<<instructon<<endl;
	//myReg->printRegValue("---> Compile and Load Instruction: ", instructon);
	myReg->printRegValue();
}

void ToolBox::executeProgram(Memory* myMem, Register* myReg){
	char* currentInstruction = NULL;
	while(myReg->getValue(Register::Reg_ProgCntr)!=myReg->getValue(Register::Reg_ProgLimit)){
		currentInstruction = myMem->memRead(myReg->getValue(Register::Reg_ProgCntr), 4);
		execute(currentInstruction, myMem, myReg);
		cout<<"~~~ Execute Binary Instruction: "<<currentInstruction<<endl;
		//myReg->printRegValue("---> Executing Binary Instruction: ", currentInstruction);
		myReg->printRegValue();
	}
}

void ToolBox::execute(char* binaryInstructionString, Memory* myMem, Register* myReg){
	int* instComp = Compiler::extractBinaryInstruction(binaryInstructionString);
	int operand = instComp[0];
	int regRs, regRt, regRd;
	int imm;


	if(operand==Compiler::OPCODE_LW){	// -> lw $Rt, imm($Rs)
		regRs = instComp[1];
		regRt = instComp[2];
		imm = instComp[3];


		int memAddress = myReg->getValue(regRs)+imm*4;
		int value = ToolBox::convertBinaryString2Integer(myMem->memRead(memAddress, 4));
		myReg->setValue(Register::Reg_MAR, memAddress);
		myReg->setValue(Register::Reg_MDR, value);
		myReg->setValue(regRt, value);
		myReg->setValue(Register::Reg_ProgCntr, (myReg->getValue(Register::Reg_ProgCntr)+4));

	}else if(operand==Compiler::OPCODE_SW){		// -> sw $Rt, imm($Rs)
		regRs = instComp[1];
		regRt = instComp[2];
		imm = instComp[3];


		int memAddress = myReg->getValue(regRs)+imm*4;
		char* value = ToolBox::convertInteger2BinaryString(myReg->getValue(regRt), 32);
		myMem->memWrite(memAddress, value);
		myReg->setValue(Register::Reg_MAR, memAddress);
		myReg->setValue(Register::Reg_MDR, ToolBox::convertBinaryString2Integer(value));
		myReg->setValue(Register::Reg_ProgCntr, (myReg->getValue(Register::Reg_ProgCntr)+4));
	}else if(operand == Compiler::OPCODE_ADDI){		//addi $rt, $rs, immed
		regRs = instComp[1];
		regRt = instComp[2];
		imm = instComp[3];


		int sum = myReg->getValue(regRs)+imm;
		myReg->setValue(regRt, sum);
		myReg->setValue(Register::Reg_ProgCntr, (myReg->getValue(Register::Reg_ProgCntr)+4));
		myReg->setValue(Register::Reg_MAR, myReg->getValue(Register::Reg_ProgCntr));
		myReg->setValue(Register::Reg_MDR, ToolBox::convertBinaryString2Integer(binaryInstructionString));
	}
}




int ToolBox::getStringSize(char* string){
	char* ptr = string;
	int count = 0;
	for( ; *ptr != '\0'; ptr++){
		count++;
	}
	return count;
}

void ToolBox::printCharArry(char *charArry){
	for(char* ptr=charArry; *ptr!='\0'; ptr++){
		std::cout<<*ptr;
	}
}


