/*
 * Register.h
 *
 *  Created on: Feb 12, 2015
 *      Author: sdey
 */

#ifndef REGISTER_H_
#define REGISTER_H_
#include <iostream>
#include "Memory.h"
//#include "ToolBox.h"
using namespace std;

class Register {
public:
	Register();
	virtual ~Register();

	static const int Reg_ProgCntr = 777;
	static const int Reg_Flag = 666;
	static const int Reg_ProgBase = 555;
	static const int Reg_ProgLimit = 444;
	static const int Reg_MAR = 333;
	static const int Reg_MDR = 222;

	// register id below must be representable by 4-bit binary (-8 ~ 7)
	static const int Reg_R1 = -1;
	static const int Reg_R2 = -2;
	static const int Reg_R3 = -3;

	int getValue(int regType);
	void setValue(int regType, int value);
	void reset();
	static int registerMapper(const char* regNameStr);

	void printRegValue();



private:
	int val_RegR1;
	int val_RegR2;
	int val_RegR3;
	int val_ProgCntr;
	int val_FlagReg;
	int val_ProgBase;
	int val_ProgLimit;
	int val_MAR;
	int val_MDR;

};

#endif /* REGISTER_H_ */
