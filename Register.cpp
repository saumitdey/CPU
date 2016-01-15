/*
 * Register.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: sdey
 */

#include "Register.h"

Register::Register() {
	// TODO Auto-generated constructor stub
	val_RegR1=0;
	val_RegR2=0;
	val_RegR3=0;
	val_ProgCntr=Memory::Instruction_Base;
	val_FlagReg=0;
	val_MAR = 0;
	val_MDR = 0;
	val_ProgBase=Memory::Instruction_Base;
	val_ProgLimit=Memory::Instruction_Base;
}

Register::~Register() {
	// TODO Auto-generated destructor stub
}

int Register::registerMapper(const char* regNameStr){
	if(strcmp(regNameStr, "r1")==0)	return Register::Reg_R1;
	if(strcmp(regNameStr, "r2")==0)	return Register::Reg_R2;
	if(strcmp(regNameStr, "r3")==0)	return Register::Reg_R3;
}

int Register::getValue(int regType){
	if(regType==Reg_R1)		return val_RegR1;
	if(regType==Reg_R2)		return val_RegR2;
	if(regType==Reg_R3)		return val_RegR3;
	if(regType==Reg_ProgCntr)	return val_ProgCntr;
	if(regType==Reg_Flag)	return val_FlagReg;
	if(regType==Reg_ProgBase)	return val_ProgBase;
	if(regType==Reg_ProgLimit)	return val_ProgLimit;
	if(regType==Reg_MAR)	return val_MAR;
	if(regType==Reg_MDR)	return val_MDR;
}

void Register::setValue(int regType, int value){
	if(regType==Reg_R1)		val_RegR1=value;
	if(regType==Reg_R2)		val_RegR2=value;
	if(regType==Reg_R3)		val_RegR3=value;
	if(regType==Reg_ProgCntr)	val_ProgCntr=value;
	if(regType==Reg_Flag)	val_FlagReg=value;
	if(regType==Reg_ProgBase)	val_ProgBase=value;
	if(regType==Reg_ProgLimit)	val_ProgLimit=value;
	if(regType==Reg_MAR)		val_MAR = value;
	if(regType==Reg_MDR)	val_MDR = value;
}

void Register::reset(){
	val_RegR1=0;
	val_RegR2=0;
	val_RegR3=0;
	val_ProgCntr=Memory::Instruction_Base;
	val_FlagReg=0;
	val_MAR = 0;
	val_MDR = 0;
	val_ProgBase=Memory::Instruction_Base;
	val_ProgLimit=Memory::Instruction_Base;
}


void Register::printRegValue(){
	cout<<"dummy print"<<endl;
	cout<<"R1: "<<val_RegR1<<endl;
	cout<<"R2: "<<val_RegR2<<endl;
	cout<<"R3: "<<val_RegR3<<endl;
	cout<<"ProgramCounter: "<<val_ProgCntr<<endl;
	cout<<"FlagRegister: "<<val_FlagReg<<endl;
	cout<<"MAR(Memory Address Register): "<< val_MAR<<endl;
	cout<<"MDR(Memory Data Register): "<< val_MDR<<endl;
	cout<<endl;
}

