/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The LiteralPoolSourceCodeInstruction is a
 * specific instruction that tells the
 * assembler where to build literal pools.
 ******************************************/
#include <string>
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "ModificationRecords.h"
#include "LiteralPoolSourceCodeInstruction.h"

LiteralPoolSourceCodeInstruction::LiteralPoolSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{

}

int LiteralPoolSourceCodeInstruction::GetLength()
{
	return 0;
}

std::string LiteralPoolSourceCodeInstruction::ToString(){ return  GetInstructionType();}
std::string LiteralPoolSourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::LTORG;}
std::string LiteralPoolSourceCodeInstruction::GetObjectCode(){return std::string("");}
ModificationRecords LiteralPoolSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
