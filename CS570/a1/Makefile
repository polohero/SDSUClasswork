EXEC = sem
G++ = /usr/local/bin/g++


$(EXEC):
	$(G++) -o $(EXEC) Delegate.cpp ProgramUnix.cpp Thread.cpp SemaphoreSlim.cpp FileHelper.cpp DataConverter.cpp -lpthread -lrt
	rm -f *.o
	$(EXEC)

clean:
	rm -f *.o core a.out $(EXEC)





