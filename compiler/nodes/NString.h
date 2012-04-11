/**

	File:			NString.h

	Project:		DCPU-16 Tools
	Component:		Compiler

	Authors:		James Rhodes

	Description:	Declares the NString AST class.

**/

#ifndef __DCPU_COMP_NODES_STRING_H
#define __DCPU_COMP_NODES_STRING_H

#include "NExpression.h"

class NString : public NExpression {
public:
    std::string value;
    NString(std::string value) : value(value), NExpression("string") { }
	virtual AsmBlock* compile(AsmGenerator& context);
	virtual AsmBlock* reference(AsmGenerator& context);
	virtual NType& getExpressionType(AsmGenerator& context);
};

#endif