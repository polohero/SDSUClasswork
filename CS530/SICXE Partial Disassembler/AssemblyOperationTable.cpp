#include <map>
#include <iostream>
#include "AssemblyOperation.h"
#include "AssemblyOperationTable.h"

using namespace std;


bool AssemblyOperationTable::_loaded = false;
assembly_map AssemblyOperationTable::_operationTable;

/**
 * The default constructor will load the table
 * as long as the table has not already been loaded.
 */
AssemblyOperationTable::AssemblyOperationTable()
{
	if(_loaded != true)
	{
		load();
	}
}

/**
 * Currently this method will not allow an invalid
 * op code to be passed. I was still figuring out the
 * syntax when I wrote this. So, it will need to be
 * converted to return a pointer to return NULL if it's not
 * found.
 */
AssemblyOperation AssemblyOperationTable::Get(int opCode)
{
	/*if(false == IsValidOpcode(opCode))
	{
		return 0;
	}*/

	assembly_map::iterator i = _operationTable.find(opCode);

	return i->second;
}

/**
 * Checks if the op code is valid.
 */
bool AssemblyOperationTable::IsValidOpcode(int opCode)
{
	assembly_map::iterator i = _operationTable.find(opCode);

	return i != _operationTable.end();
}


void AssemblyOperationTable::insert(AssemblyOperation operation)
{
	AssemblyOperationTable table;

	// Check if the op code is already in the map. If it
	// is, then we have a problem.
	if(true == table.IsValidOpcode(operation.GetOpCode()))
	{
		throw "AssemblyOperation is already added. It cannot be added again.";
	}

	_operationTable.insert(assembly_pair(operation.GetOpCode(), operation));
}

void AssemblyOperationTable::load()
{
	_loaded = true;

	// At some point this could probably be moved
	// out to a config file. But, for now we have a fixed
	// set of operations, so there is no harm in hard coding it.

	insert( AssemblyOperation(0,"LDA","034","A <-- (m..m+2)","","LDA m"));
	insert( AssemblyOperation(4,"LDX","034","X <-- (m..m+2)","","LDX m"));
	insert( AssemblyOperation(8,"LDL","034","L <-- (m..m+2)","","LDL m"));
	insert( AssemblyOperation(12,"STA","034","m..m+2 <-- (A)","","STA m"));
	insert( AssemblyOperation(16,"STX","034","m..m+2 <-- (X)","","STX m"));
	insert( AssemblyOperation(20,"STL","034","m..m+2 <-- (L)","","STL m"));
	insert( AssemblyOperation(24,"ADD","034","A <-- (A) + (m..m+2)","","ADD m"));
	insert( AssemblyOperation(28,"SUB","034","A <-- (A) - (m..m+2)","","SUB m"));
	insert( AssemblyOperation(32,"MUL","034","A <-- (A) * (m..m+2)","","MUL m"));
	insert( AssemblyOperation(36,"DIV","034","A : (A) / (m..m+2)","","DIV m"));
	insert( AssemblyOperation(40,"COMP","034","A : (m..m+2)","","COMP m"));
	insert( AssemblyOperation(44,"TIX","034","X <-- (X) + 1; (X) : (m..m+2)","C","TIX m"));
	insert( AssemblyOperation(48,"JEQ","034","PC <-- m if CC set to =","","JEQ m"));
	insert( AssemblyOperation(52,"JGT","034","PC <-- m if CC set to >","","JGT m"));
	insert( AssemblyOperation(56,"JLT","034","PC <-- m if CC set to <","","JLT m"));
	insert( AssemblyOperation(60,"J","034","PC <-- m","","J m"));
	insert( AssemblyOperation(64,"AND","034","A <-- (A) & (m..m+2)","","AND m"));
	insert( AssemblyOperation(68,"OR","034","A <-- (A) | (m..m+2)","","OR m"));
	insert( AssemblyOperation(72,"JSUB","034","L <-- (PC); PC <-- m","","JSUB m"));
	insert( AssemblyOperation(76,"RSUB","34","PC <-- (L)","","RSUB"));
	insert( AssemblyOperation(80,"LDCH","034","A [rightmost byte] <-- (m)","","LDCH m"));
	insert( AssemblyOperation(84,"STCH","034","m <-- (A) [rightmost byte]","","STCH m"));
	insert( AssemblyOperation(88,"ADDF","34","F <-- (F) + (m..m+5)","X F","ADDF m"));
	insert( AssemblyOperation(92,"SUBF","34","F <-- (F) - (m..m+5)","X F","SUBF m"));
	insert( AssemblyOperation(96,"MULF","34","F <-- (F) * (m..m+5)","X F","MULF m"));
	insert( AssemblyOperation(100,"DIVF","34","F : (F) / (m..m+5)","X F","DIVF m"));
	insert( AssemblyOperation(104,"LDB","34","B <-- (m..m+2) X","","LDB m"));
	insert( AssemblyOperation(108,"LDS","34","S <-- (m..m+2)","X","LDS m"));
	insert( AssemblyOperation(112,"LDF","34","F <-- (m..m+5) X F","","LDF m"));
	insert( AssemblyOperation(116,"LDT","34","T <-- (m..m+2)","X","LDT m"));
	insert( AssemblyOperation(120,"STB","34","m..m+2 <-- (B)","X","STB m"));
	insert( AssemblyOperation(124,"STS","34","m..m+2 <-- (S)","X","STS m"));
	insert( AssemblyOperation(128,"STF","34","m..m+5 <-- (F)","X","STF m"));
	insert( AssemblyOperation(132,"STT","34","m..m+2 <--(T)","X","STT m"));
	insert( AssemblyOperation(136,"COMPF","34","F : (m..m+5)","X F C","COMPF m"));
	insert( AssemblyOperation(144,"ADDR","2","r2 <-- (r2) + (r1)","X","ADDR r1,r2"));
	insert( AssemblyOperation(148,"SUBR","2","r2 <-- (r2) - (r1)","X","SUBR r1,r2"));
	insert( AssemblyOperation(152,"MULR","2","r2 <-- (r2) * (r1)","X","MULR r1,r2"));
	insert( AssemblyOperation(156,"DIVR","2","(r2) <-- (r2) / (r1)","X","DIVR r1,r2"));
	insert( AssemblyOperation(160,"COMPR","2","(r1) : (r2)","X F C","COMPR r1,r2"));
	insert( AssemblyOperation(164,"SHIFTL","2","r1 <-- (r1); left circular shift n bits. {In assembled instruction, r2=n-1}","X","SHIFTL r1,n"));
	insert( AssemblyOperation(168,"SHIFTR","2","r1 <-- (r1); right shift n bits with vacated bit positions set equal to leftmost bit of (r1). {In assembled instruction, r2=n-1}","X","SHIFTR r1,n"));
	insert( AssemblyOperation(172,"RMO","2","r2 <-- (r1)","X","RMO r1,r2"));
	insert( AssemblyOperation(176,"SVC","2","Generate SVC interrupt. {In assembled instruction, r1=n}","X","SVC n (r2 is ignored)."));
	insert( AssemblyOperation(180,"CLEAR","2","r1 <-- 0","X","CLEAR r1 (r2 is ignored)"));
	insert( AssemblyOperation(184,"TIXR","2","X <-- (X) + 1; (X) : (r1)","X C","TIXR r1 (r2 is ignored)"));
	insert( AssemblyOperation(192,"FLOAT","1","F <-- (A) [convert to floating]","X F","FLOAT"));
	insert( AssemblyOperation(196,"FIX","1","A <-- (F) [convert to integer]","X F","FIX"));
	insert( AssemblyOperation(200,"NORM","1","F <-- (F) [normalized]","X F","NORM"));
	insert( AssemblyOperation(208,"LPS","34","Load processor status from information beginning at address m (see Section6.2.1)","P X ","LPS m"));
	insert( AssemblyOperation(212,"STI","34","Interval timer value <-- (m..m+2) (see Section 6.2.1)","P X","STI m"));
	insert( AssemblyOperation(216,"RD","034","A [rightmost byte] <-- data from device specified by (m)","P","RD m"));
	insert( AssemblyOperation(220,"WD","034","Device specified by (m) <-- (A)","P","WD m"));
	insert( AssemblyOperation(224,"TD","034","Test device specified by (m)","P C","TD m"));
	insert( AssemblyOperation(232,"STSW","034"," m..m+2 <-- (SW) P","","STSW m"));
	insert( AssemblyOperation(236,"SSK","34","Protection key for address m <-- (A) (see Section 6.2.4)","P X","SSK m"));
	insert( AssemblyOperation(240,"SIO","1","Start I/O channel number (A); address of channel program is given by (S)","P X","SIO"));
	insert( AssemblyOperation(244,"HIO","1","Halt I/O channel number (A)","P X","HIO"));
	insert( AssemblyOperation(248,"TIO","1","Test I/O channel number (A)","P X C","TIO"));


}

