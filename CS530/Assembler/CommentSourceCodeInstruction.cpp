/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The CommentSourceCodeInstruction is a
 * specific instruction that is essentially
 * a skip instruction. There is nothing that
 * happens because of a comment. We chose
 * this route instead of just ignoring the
 * lines because we could then include
 * comments in a debugging intermidate file
 * if needed.
 ******************************************/
#include <string>
#include "SourceCodeLine.h"
#include "SourceCodeInstruction.h"
#include "ModificationRecords.h"
#include "CommentSourceCodeInstruction.h"

CommentSourceCodeInstruction::CommentSourceCodeInstruction(
	SourceCodeLine line) : SourceCodeInstruction(line)
{

}

int CommentSourceCodeInstruction::GetLength()
{
	return 0;
}

std::string CommentSourceCodeInstruction::ToString(){ return  GetInstructionType() + std::string(":") + _line.GetRawLine();}
std::string CommentSourceCodeInstruction::GetInstructionType(){return SourceCodeInstruction::COMMENT;}
std::string CommentSourceCodeInstruction::GetObjectCode(){return std::string("");}
ModificationRecords CommentSourceCodeInstruction::GetModificationRecords()
{
		ModificationRecords records;
		return records;
}
