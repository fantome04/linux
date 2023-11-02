CXX = g++
TARGET = myShell

run: $(TARGET)
	./$(TARGET)

$(TARGET): myShell.o
	$(CXX) myShell.o -o $(TARGET)

myShell.o: myShell.cpp
	$(CXX) myShell.cpp -c

clean:
	rm -f $(TARGET) *.o
