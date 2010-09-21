
OBJ = testsig.o ../GraphicSignal.o ../RingBuffer.o ../Signal.o
CXXFLAGS = -I../../lib -I..

testsig : $(OBJ)
	g++ $(OBJ) -o testsig

compile:
	g++ ../GraphicSignal.cpp -c $(CXXFLAGS)

clean:
	rm -f $(OBJ) testsig

testsig.o : ../GraphicSignal.h ../Signal.h ../RingBuffer.h
../GraphicSignal.o : ../GraphicSignal.h ../Signal.h 
../Signal.o : ../Signal.h
../RingBuffer.o : ../RingBuffer.h