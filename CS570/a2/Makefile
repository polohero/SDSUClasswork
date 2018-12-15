EXEC = a2
G++ = /usr/local/bin/g++


$(EXEC):
	$(G++) -o $(EXEC) Page.cpp DataConverter.cpp FileHelper.cpp PageTable.cpp Program.cpp PageReplacementAlgorithm.cpp Fifo.cpp LRU.cpp Clock.cpp ClockNode.cpp Optimal.cpp SecondChanceFifo.cpp
	rm -f *.o
	$(EXEC)

clean:
	rm -f *.o core a.out $(EXEC)





