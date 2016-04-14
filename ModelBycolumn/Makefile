
CFLAGS=-Wall -O
#CFLAGS=-Wall -g
CPPFLAGS=-DNDEBUG -DIL_STD
CXX=g++
OBJ=model.o
 
model: $(OBJ)
	$(CXX) $(CFLAGS) -o model $(OBJ)  -lm -lilocplex -lconcert -lcplex -lpthread
 
model.o: model.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c model.cpp
 
clean:
	rm -f model model.o