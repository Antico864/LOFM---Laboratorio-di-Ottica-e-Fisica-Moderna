CXX := g++
LIBS := `root-config --libs`
INCS := `root-config --cflags`
CXXFLAGS := -g3 -Wall --pedantic -std=c++11
myLIBS := funzioni.o

EXECUTABLES = mlk
OBJECTS = $(myLIBS) $(EXECUTABLES:=.o)

.PHONY: all clean

## Compila tutto
#all: $(EXECUTABLES)

## Regola generica per gli eseguibili
${EXECUTABLES}: ${EXECUTABLES}.cpp $(myLIBS)
	@echo "Linking $@..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) ${INCS}

## Regola generica per costruire file .o
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c -o $@ $< ${INCS}

## Dipendenze esplicite per i file oggetto comuni
funzioni.o: funzioni.cpp funzioni.hpp

## Pulizia
clean:
	@rm -f mlk *.o
	@rm -rf mlk.dSYM
	@rm -f mlk.pdf