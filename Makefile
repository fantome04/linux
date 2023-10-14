CXX = g++
TARGET = main

run: $(TARGET)
	./$(TARGET)

$(TARGET): main.o ComplexNum.o
	$(CXX) main.o ComplexNum.o -o $(TARGET)

main.o: main.cpp
	$(CXX) main.cpp -c

ComplexNum.o: ComplexNum.cpp ComplexNum.hpp
	$(CXX) ComplexNum.cpp -c

clean:
	rm -f $(TARGET) *.o
