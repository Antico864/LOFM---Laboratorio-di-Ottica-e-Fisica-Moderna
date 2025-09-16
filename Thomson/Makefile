CXX := g++
CXXFLAGS := -g3 -Wall --pedantic -std=c++17 -stdlib=libc++ $(shell root-config --cflags)
LIBS := $(shell root-config --libs)

thm: thomson.o regression.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@rm -f thm *.o
	@rm -rf thm.dSYM