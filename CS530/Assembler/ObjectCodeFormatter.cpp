/******************************************
 * Authors: Cory Wixom / Garrett Chandley
 * Unix Logins: masc0751   / masc0745
 * Class: CS 530 Spring 2013
 * Date: 04/02/2013
 *
 * The ObjectCodeFormatter is in charge of
 * formatting the object code for a specific
 * source file. It will perform the Pass 2
 * logic where the parsed source code turns into
 * object code.
 ******************************************/

#include <string>
#include "DataConverter.h"
#include "SourceCodeFile.h"
#include "SourceCodeInstruction.h"
#include "ObjectCodeFormatter.h"
#include "ModificationRecords.h"
#include "ModificationRecord.h"

#define LEADING_ZERO '0'
#define SPACE ' '
#define NEWLINE '\n'

#define HEADER_START 'H'
#define HEADER_PROGRAM_NAME_LENGTH 6
#define HEADER_STARTING_ADDRESS_LENGTH 6
#define HEADER_MEMORY_SIZE_LENGTH 6

#define TEXT_START 'T'
#define TEXT_STARTING_ADDRESS_LENGTH 6
#define TEXT_OBJECT_CODE_LENGTH_LENGTH 2
#define TEXT_OBJECT_CODE_LENGTH 30

#define END_START 'E'
#define END_ADDRESS_LENGTH 6

#define MOD_START 'M'
#define MOD_STARTING_ADDRESS_LENGTH 6
#define MOD_LENGTH_LENGTH 2

using namespace std;

string ObjectCodeFormatter::GetErrorMessages(){return _errorMessages;}

string ObjectCodeFormatter::FormatFile(SourceCodeFile* file)
{
	validate(file);
	return 	formatFile(file);
}

void ObjectCodeFormatter::handleErrorMessages(char const* errorMessage, int lineNumber)
{
	_errorMessages += "Line: " + DataConverter::GetIntToString(lineNumber) + ": ";
	string error = errorMessage;
	_errorMessages += error + "\n";
}

string ObjectCodeFormatter::formatFile(SourceCodeFile* file)
{
	int lineNumber = 1;

	string objectCode;

	SourceCodeInstruction* start =
		file->Get(0);

	SourceCodeInstruction* end;

	for(int i = file->Size()-1; i >= 0; i--)
	{
		SourceCodeInstruction* possibleEnd =
			file->Get(i);

		if( possibleEnd->GetInstructionType().compare( SourceCodeInstruction::END ) == 0)
		{
			end = possibleEnd;
			break;
		}
	}

	if( end == 0)
	{
		throw "ObjectCodeFormatter: All source files must end with an END instruction.";
	}

	ModificationRecords records;

	try
	{
		/************************************************************
			Header record
			Col 1H
			Col 2-7program name
			Col 8-13starting address (hex)
			Col 14-19 length of object program in bytes (hex)
		*************************************************************/
		objectCode += HEADER_START;

		objectCode += DataConverter::PadRight(
						start->GetSourceCodeLine().GetLabel(),
						HEADER_PROGRAM_NAME_LENGTH,
						SPACE);

		objectCode += DataConverter::PadLeft(
						DataConverter::ConvertIntToHex(file->GetStartingLocation()),
						HEADER_STARTING_ADDRESS_LENGTH,
						LEADING_ZERO);

		objectCode += DataConverter::PadLeft(
					DataConverter::ConvertIntToHex(file->GetMemorySize()),
					HEADER_MEMORY_SIZE_LENGTH,
					LEADING_ZERO);

		objectCode += NEWLINE;
	}
	catch(char const* exception)
	{
		handleErrorMessages(exception, lineNumber);
	}
	catch(...)
	{
		handleErrorMessages("Unknown exception", lineNumber);
	}



	/************************************************************
		Text record
		Col 1 T
		Col 2-7starting address in this record (hex)
		Col 8-9length of object code in this record in bytes (hex)
		Col 10-69 object code (69-10+1)/6=10 instructions
	************************************************************/

	int currentLocationCount = 0;
	int currentStartingInstruction = 0;
	string textRecord;
	SourceCodeInstruction* first;

	for( int i = 1; i < file->Size(); i++)
	{
		lineNumber++;

		try
		{
			SourceCodeInstruction* instruction =
				file->Get(i);

			if( instruction->GetInstructionType().compare(SourceCodeInstruction::END ) == 0 )
			{
				continue;
			}
			// This will skip any instructions
			// that don't product object code.
			// IE comments etc...
			if( instruction->GetLength() == 0 )
			{
				continue;
			}

			// We need to keep track of the first
			// instruction. The END may need it.
			if( first == 0 )
			{
				first = instruction;
			}

			// Store any modification records
			// They will be used later on.
			ModificationRecords currentRecords;

			// If it's a RESB or RESW. Create a new line.
			// Those bytes need to be reserved.
			if( instruction->GetInstructionType().compare(SourceCodeInstruction::RESB) == 0 ||
				instruction->GetInstructionType().compare(SourceCodeInstruction::RESW) == 0 ||
				(currentLocationCount + instruction->GetLength()) > TEXT_OBJECT_CODE_LENGTH )
			{
				if( textRecord.compare(string("")) != 0 )
				{
					objectCode += TEXT_START;
					objectCode += DataConverter::PadLeft(
									DataConverter::ConvertIntToHex(currentStartingInstruction),
									TEXT_STARTING_ADDRESS_LENGTH,
									LEADING_ZERO);
					objectCode += DataConverter::PadLeft(
									DataConverter::ConvertIntToHex(currentLocationCount),
									TEXT_OBJECT_CODE_LENGTH_LENGTH,
									LEADING_ZERO);
					objectCode += textRecord;
					objectCode += NEWLINE;

					currentLocationCount = 0;
					currentStartingInstruction = 0;
					textRecord = "";
				}
			}

			// If the previous instruction was a RESB or RESW
			// we need to continue on until we finally
			// find our next "real" instruction.
			if( instruction->GetInstructionType().compare(SourceCodeInstruction::RESB) == 0 ||
				instruction->GetInstructionType().compare(SourceCodeInstruction::RESW) == 0)
			{
				continue;
			}

			// Store the current location
			// to be put in the next text record.
			if( textRecord.compare(string("")) == 0 )
			{
				currentStartingInstruction = instruction->GetLocation();
			}

			currentLocationCount += instruction->GetLength();
			textRecord += instruction->GetObjectCode();

			currentRecords = instruction->GetModificationRecords();

			for(int i = 0; i < currentRecords.Size(); i++)
			{
				records.Add(currentRecords.Get(i));
			}

		}
		catch(char const* exception)
		{
			handleErrorMessages(exception, lineNumber);
		}
		catch(...)
		{
			handleErrorMessages("Unknown exception", lineNumber);
		}
	}

	// Finally, add the final text record into
	// the object code.
	if( textRecord.compare(string("")) != 0 )
	{
		objectCode += TEXT_START;
		objectCode += DataConverter::PadLeft(
						DataConverter::ConvertIntToHex(currentStartingInstruction),
						TEXT_STARTING_ADDRESS_LENGTH,
						LEADING_ZERO);
		objectCode += DataConverter::PadLeft(
						DataConverter::ConvertIntToHex(currentLocationCount),
						TEXT_OBJECT_CODE_LENGTH_LENGTH,
						LEADING_ZERO);
		objectCode += textRecord;
		objectCode += NEWLINE;

		currentLocationCount = 0;
		currentStartingInstruction = 0;
		textRecord = "";

	}

	/*************************************************************
		Modification record
		Col 1M
		Col 2-7Starting location of the address field to be modified,
		relative to the beginning of the program
		Col 8-9length of the address field to be modified, in half-
		bytes
	*************************************************************/
	if( file->GetStartingLocation() == 0)
	{
		for(int i = 0; i < records.Size(); i++)
		{
			objectCode += MOD_START;
			objectCode += DataConverter::PadLeft(
							DataConverter::ConvertIntToHex(
								records.Get(i).GetLocation()),
							MOD_STARTING_ADDRESS_LENGTH,
							LEADING_ZERO);
			objectCode += DataConverter::PadLeft(
							DataConverter::ConvertIntToHex(
								records.Get(i).GetLength()),
							MOD_LENGTH_LENGTH,
							LEADING_ZERO);
			objectCode += NEWLINE;

		}
	}


	/*************************************************************
		End record
		Col 1E
		Col 2-7address of first executable instruction (hex)
	*************************************************************/
	objectCode += END_START;
	if( end->GetObjectCode().compare(string("")) == 0 )
	{
		objectCode += DataConverter::PadLeft(
						DataConverter::ConvertIntToHex(first->GetLocation()),
						END_ADDRESS_LENGTH,
						LEADING_ZERO);
	}
	else
	{
		objectCode += DataConverter::PadLeft(
						end->GetObjectCode(),
						END_ADDRESS_LENGTH,
						LEADING_ZERO);
	}

	if( _errorMessages.compare(string("")) == 0)
	{
		return objectCode;
	}
	else
	{
		return string("");
	}
}


void  ObjectCodeFormatter::validate(SourceCodeFile* file)
{
	if( file->Size() == 0 )
	{
		throw "ObjectCodeFormatter: Nothing located in the SourceCodeFile.";
	}

	SourceCodeInstruction* start =
		file->Get(0);

	if( start->GetInstructionType().compare( SourceCodeInstruction::START ) != 0)
	{
		throw "ObjectCodeFormatter: All source files must begin with a start.";
	}

	SourceCodeInstruction* end;

	for(int i = file->Size()-1; i >= 0; i--)
	{
		SourceCodeInstruction* possibleEnd =
			file->Get(i);

		if( possibleEnd->GetInstructionType().compare( SourceCodeInstruction::END ) == 0)
		{
			end = possibleEnd;
			break;
		}
	}

	if( end == 0)
	{
		throw "ObjectCodeFormatter: All source files must end with an END instruction.";
	}
}
