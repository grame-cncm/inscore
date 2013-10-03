
OBJ = testsig.o ../GraphicSignal.o ../RingBuffer.o ../TSignal.o
CXXFLAGS = -I../../libmapping/src/misc -I..

testsig : $(OBJ)
	g++ $(OBJ) -o testsig

compile:
	g++ ../GraphicSignal.cpp -c $(CXXFLAGS)

clean:
	rm -f $(OBJ) testsig

testsig.o : ../GraphicSignal.h ../TSignal.h ../RingBuffer.h
../GraphicSignal.o : ../GraphicSignal.h ../TSignal.h 
../TSignal.o : ../TSignal.h
../RingBuffer.o : ../RingBuffer.h