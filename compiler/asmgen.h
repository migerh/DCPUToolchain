/**

	File:			asmgen.h

	Project:		DCPU-16 Tools
	Component:		Compiler

	Authors:		James Rhodes

	Description:	Declares the classes used to assist AST
					nodes in generating assembly.

**/

#ifndef __DCPU_COMP_ASMGEN_H
#define __DCPU_COMP_ASMGEN_H

class Assembler;

#include <cstdint>
#include <exception>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "asmtypes.h"
#include "nodes/NType.h"
#include "nodes/NDeclarations.h"
#include "nodes/NFunctionDeclaration.h"

class AsmBlock
{
private:
	std::string m_Assembly;

    typedef std::basic_ostream<char, std::char_traits<char> > _couttype;
    typedef _couttype& (*_stdendl)(_couttype&);

public:
	AsmBlock();
	
	friend AsmBlock& operator<< (AsmBlock& block, char& input);
	friend AsmBlock& operator<< (AsmBlock& block, const size_t& input);
	friend AsmBlock& operator<< (AsmBlock& block, const char input[]);
	friend AsmBlock& operator<< (AsmBlock& block, std::ifstream& input);
	friend AsmBlock& operator<< (AsmBlock& block, const std::string& input);
	friend AsmBlock& operator<< (AsmBlock& block, const AsmBlock& input);
	friend std::ostream& operator<< (std::ostream& output, const AsmBlock& block);
    AsmBlock& operator<<(_stdendl manip)
    {
		std::stringstream sstr;
		sstr << std::endl;
		this->m_Assembly += sstr.str();
        return *this;
    }
};

class StackFrame
{
public:
	typedef std::map<std::string, NType&> StackMap;
	typedef std::pair<std::string, NType&> StackPair;

private:
	AsmGenerator& m_Generator;
	StackMap m_StackMap;

public:
	StackFrame(AsmGenerator& generator, StackMap& map) : m_StackMap(map), m_Generator(generator) { };
	int32_t getPositionOfVariable(std::string name);
	NType* getTypeOfVariable(std::string name);
	uint16_t getSize();
};

class AsmGenerator
{
private:
	const Assembler* m_AssemblerTarget;
	std::vector<std::string> m_AutomaticLabels;
	static char getRandomCharacter();
	static std::string getRandomString(std::string::size_type sz);

public:
	AsmBlock m_Preassembly;
	AsmBlock m_Postassembly;
	StackFrame* m_CurrentFrame;
	NDeclarations* m_RootNode;

public:
	AsmGenerator(std::string asmtarget);
	
	NFunctionDeclaration* getFunction(std::string name);
	StackFrame* generateStackFrame(NFunctionDeclaration* function, bool referenceOnly = true);
	void finishStackFrame(StackFrame* frame);
	std::string getRandomLabel(std::string prefix);
	inline const Assembler& getAssembler() { return *(this->m_AssemblerTarget); }
	inline bool isAssemblerDebug() { return true; }
};

class CompilerException : public std::exception
{
private:
	std::string m_Message;

public:
	CompilerException(std::string message) : m_Message(message) { };
	virtual const char* what() const throw()
	{
		return this->m_Message.c_str();
	}
	inline std::string getMessage() { return this->m_Message; }
};

#endif