/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The EndSourceCodeInstruction is a specific
 * instruction that is the last instruction
 * that appears in the source code file.
 ******************************************/
#include <string>
#include "DataConverter.h"
#include "SymbolTable.h"
#include "SourceCodeLine.h"
#include "ModificationRecords.h"
#include "SourceCodeInstruction.h"
#include "EndSourceCodeInstruction.h"

using namespace std;

EndSourceCodeInstruction::EndSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{

}


int EndSourceCodeInstruction::GetLength(){return 0;}
string EndSourceCodeInstruction::ToString(){return GetInstructionType() + string(":") +  _line.GetOperand();}
string EndSourceCodeInstruction::GetInstructionType(){ return SourceCodeInstruction::END;}
string EndSourceCodeInstruction::GetObjectCode()
{
	if( _line.GetOperand().compare(string("")) == 0 )
	{
		return string("");
	}

	Symbol* symbol =
		SymbolTable::Get(_line.GetOperand());

	return DataConverter::ConvertIntToHex(symbol->GetAddress());
}
ModificationRecords EndSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
