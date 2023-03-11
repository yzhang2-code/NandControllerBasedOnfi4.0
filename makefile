CXX = g++
CXXFLAGS = -Wall -O0 -lrt -std=c++0x


main: main.o onfi_head.o microprocessor_interface.o
	$(CXX) -o main main.o onfi_head.o microprocessor_interface.o $(CXXFLAGS) 

main.o: main.cpp onfi_head.h
	$(CXX) -c main.cpp $(CXXFLAGS) 

onfi_head.o: onfi_head.h microprocessor_interface.h

microprocessor_interface.o: microprocessor_interface.h hardware_locations.h

clean:
	rm *.o