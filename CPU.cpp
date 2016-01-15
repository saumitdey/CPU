#include <iostream>
#include <cstring>
#include "Memory.h"
#include "Register.h"
#include "Compiler.h"
#include "ToolBox.h"

using namespace std;

/*
 * Assumption:
 * 	- using 2's complement for binary representation
 */

int main(){

	Memory* bestMem = new Memory();
	Register* bestRegs = new Register();

/*
	// testing Binary Integer Conversion
	cout<<"integer to binary: "<<endl<<"	"
			<<ToolBox::convertInteger2BinaryString(11, 32)<<endl;
	cout<<"integer to binary: "<<endl<<"	"
			<<ToolBox::convertInteger2BinaryString(-11, 32)<<endl;
	char binIntTester[32] = "110111101";
	cout<<"binary to integer:"<<endl<<"	"
			<<ToolBox::convertBinaryString2Integer(binIntTester)<<endl;

	// testing Memory Read/Write
	char memTest[50]="10011001";
	bestMem->memWrite(50, memTest);		// this writes 4 bytes at a time with value equivalent to the binary given
	cout<<"Memory Read Test:"<<endl; cout<<"	";
		ToolBox::printCharArry(bestMem->memRead(50, 4));;


	// register parsing test
	cout<<"Instruction to binary string test:"<<endl<<"	";
		ToolBox::printCharArry(Compiler::compileInstrToBinarySting("lw $rt, -17($rs)"));
	cout<<"extract binary Instruction test:"<<endl;
		//char *instructionExtractionTester = Compiler::compileInstrToBinarySting("lw $rt, -171($rs)");
		char *instructionExtractionTester = Compiler::compileInstrToBinarySting("addi $rt, $rs, -55");
		int* extractTester = Compiler::extractBinaryInstruction(instructionExtractionTester);
		cout<<"	opcode: "<<extractTester[0]<<endl;
		cout<<"	Rs: "<<extractTester[1]<<endl;
		cout<<"	Rt: "<<extractTester[2]<<endl;
		cout<<"	IMM: "<<extractTester[3]<<endl;


	// execution test
	bestMem->memReset();
	bestRegs->reset();
	char* SW_instrcn = "sw $rt, -20($rs)";
	char* LW_instrcn = "lw $rt, -20($rs)";
	char *ADDI_instrcn = "addi $rt, $rs, -200";
		bestRegs->setValue(Register::Reg_Rs, 4*30);
		bestRegs->setValue(Register::Reg_Rt, -30);
	ToolBox::execute(Compiler::compileInstrToBinarySting(ADDI_instrcn), bestMem, bestRegs);		// now Rt=4*30-200 = -80
	ToolBox::execute(Compiler::compileInstrToBinarySting(SW_instrcn), bestMem, bestRegs);
	//bestMem->memDump(0, 20);
		bestRegs->setValue(Register::Reg_Rt, -1);	cout<<"Reg_Rt: "<<bestRegs->getValue(Register::Reg_Rt)<<endl;
		ToolBox::execute(Compiler::compileInstrToBinarySting(LW_instrcn), bestMem, bestRegs);	cout<<"Reg_Rt: "<<bestRegs->getValue(Register::Reg_Rt)<<endl;
*/

	// File Reading Test:

	/*
	 * Real Run:	// initially value($rs)=0
	 *		addi $rt, $rs, -200		#rt=-200
	 *		sw   $rt, 50($rs)
	 *
	 *		addi $rt, $rs, 500		#rt=500
	 *		sw   $rt, 55($rs)
	 *
	 *		lw   $rt, 50($rs)		#rt=-200
	 *
	 */
	cout<<"=======================REAL RUN===================="<<endl;
	bestMem->memReset();
	bestRegs->reset();

	ToolBox::loadProgram("Instructions.myasm", bestMem, bestRegs, Memory::Instruction_Base);
	ToolBox::executeProgram(bestMem, bestRegs);
	bestMem->memDump(0, 500);



	//execute instruction
/*	char* temp;
	ToolBox::printCharArry(temp = bestMem->memRead(bestRegs->getValue(Register::Reg_ProgCntr), 4));
	ToolBox::execute(temp, bestMem, bestRegs);
		bestRegs->setValue(Register::Reg_ProgCntr, bestRegs->getValue(Register::Reg_ProgCntr)+4);

	ToolBox::printCharArry(temp = bestMem->memRead(bestRegs->getValue(Register::Reg_ProgCntr), 4));
	ToolBox::execute(temp, bestMem, bestRegs);
			bestRegs->setValue(Register::Reg_ProgCntr, bestRegs->getValue(Register::Reg_ProgCntr)+4);

	ToolBox::printCharArry(temp = bestMem->memRead(bestRegs->getValue(Register::Reg_ProgCntr), 4));
	ToolBox::execute(temp, bestMem, bestRegs);
		bestRegs->setValue(Register::Reg_ProgCntr, bestRegs->getValue(Register::Reg_ProgCntr)+4);

	ToolBox::printCharArry(temp = bestMem->memRead(bestRegs->getValue(Register::Reg_ProgCntr), 4));
	ToolBox::execute(temp, bestMem, bestRegs);
		bestRegs->setValue(Register::Reg_ProgCntr, bestRegs->getValue(Register::Reg_ProgCntr)+4);

	ToolBox::printCharArry(temp = bestMem->memRead(bestRegs->getValue(Register::Reg_ProgCntr), 4));
	ToolBox::execute(temp, bestMem, bestRegs);
		bestRegs->setValue(Register::Reg_ProgCntr, bestRegs->getValue(Register::Reg_ProgCntr)+4);

	//bestMem->memDump(bestMem->getDataBase()+50*4-3,10);
	bestMem->memDump(0,500);
*/


	return 0;
}
