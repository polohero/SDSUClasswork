EXEC = diss
G++ = /usr/local/bin/g++


$(EXEC):
	$(G++) -o $(EXEC) FormatFourInstruction.cpp FormatThreeInstruction.cpp FormatTwoInstruction.cpp FormatOneInstruction.cpp FormatZeroInstruction.cpp Instruction.cpp InstructionFactory.cpp AssemblyOperation.cpp AssemblyOperationTable.cpp DataConverter.cpp Memory.cpp Registers.cpp Program.cpp
	rm -f *.o
	$(EXEC)

clean:
	rm -f *.o core a.out $(EXEC)





