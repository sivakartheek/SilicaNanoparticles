CEXE = main
CSRC := $(CEXE).cpp Configuration.cpp Averages.cpp
COBJ := $(patsubst %.cpp,%.o,$(CSRC))

all:$(CEXE)

$(CEXE):$(COBJ)
	g++ $(COBJ) -o $@ -lm

main.o:main.cpp
	g++ -c main.cpp

Configuration.o:Configuration.cpp
	g++ -c Configuration.cpp

Averages.o:Averages.cpp
	g++ -c Averages.cpp

clean:
	rm -f $(CEXE) $(COBJ) 


