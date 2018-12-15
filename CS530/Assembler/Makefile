EXEC = scl
G++ = /usr/local/bin/g++


$(EXEC):
	$(G++) -o $(EXEC) WordCharSourceCodeInstruction.cpp WordHexSourceCodeInstruction.cpp EquSourceCodeInstruction.cpp Program.cpp Literal.cpp LiteralPoolSourceCodeInstruction.cpp LiteralTable.cpp LiteralSourceCodeInstruction.cpp BaseSourceCodeInstruction.cpp Format3SourceCodeInstruction.cpp Format4SourceCodeInstruction.cpp Format2SourceCodeInstruction.cpp Format1SourceCodeInstruction.cpp ModificationRecords.cpp ModificationRecord.cpp EndSourceCodeInstruction.cpp ObjectCodeFormatter.cpp WordIntSourceCodeInstruction.cpp ReswSourceCodeInstruction.cpp ResbSourceCodeInstruction.cpp Format0SourceCodeInstruction.cpp StartSourceCodeInstruction.cpp ByteCharSourceCodeInstruction.cpp ByteIntSourceCodeInstruction.cpp ByteHexSourceCodeInstruction.cpp SourceCodeLine.cpp SourceCodeInstruction.cpp DataConverter.cpp AssemblyOperationTable.cpp AssemblyOperation.cpp SourceCodeInstructionFactory.cpp CommentSourceCodeInstruction.cpp SourceCodeFile.cpp SymbolTable.cpp Symbol.cpp
	rm -f *.o
	$(EXEC)

clean:
	rm -f *.o core a.out $(EXEC)





