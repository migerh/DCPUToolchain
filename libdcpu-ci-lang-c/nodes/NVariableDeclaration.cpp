/**

	File:		NVariableDeclaration.cpp

	Project:	DCPU-16 Tools
	Component:	LibDCPU-ci-lang-c

	Authors:	James Rhodes

	Description:	Defines the NVariableDeclaration AST class.

**/

#include <AsmGenerator.h>
#include <CompilerException.h>
#include "NVariableDeclaration.h"

AsmBlock* NVariableDeclaration::compile(AsmGenerator& context)
{
	// If we have no initialization expression, we don't need to do anything.
	if (this->initExpr == NULL)
		return NULL;

	// Create our new block.
	AsmBlock* block = new AsmBlock();

	// Add file and line information.
	*block << this->getFileAndLineState();

	// When an expression is evaluated, the result goes into the A register.
	AsmBlock* expr = this->initExpr->compile(context);
	*block << *expr;
	delete expr;
	
	// get variable type
	IType* varType = context.m_CurrentFrame->getTypeOfVariable(this->id.name);
	
	// get type, it may has to be cast
	IType* exprType = this->initExpr->getExpressionType(context);
	
	// cast to rhs to lhs type
	if (exprType->implicitCastable(context, varType))
	{
		*block << *(exprType->implicitCast(context, varType, 'A'));
	}
	else
	{
		throw new CompilerException(this->line, this->file, 
		"Unable to implicitly cast '" + exprType->getName()
		+ "' to '" + varType->getName() + "'");
	}
	


	// Get the position of the variable.
	TypePosition result = context.m_CurrentFrame->getPositionOfVariable(this->id.name);

	if (!result.isFound())
		throw new CompilerException(this->line, this->file, "The variable '" + this->id.name + "' was not found in the scope.");

	// Set the value of the variable directly.
	*block << result.pushAddress('I');
	// save the value A to [I]
	*block << *(varType->saveToRef(context, 'A', 'I'));

	return block;
}

AsmBlock* NVariableDeclaration::reference(AsmGenerator& context)
{
	throw new CompilerException(this->line, this->file, "Unable to get reference to the result of a variable.");
}
