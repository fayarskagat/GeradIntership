
CFLAGS=-Wall -O
#CFLAGS=-Wall -g
CPPFLAGS=-DNDEBUG -DIL_STD
CXX=g++
OBJ=shortest_path.o
 
shortest_path: $(OBJ)
	$(CXX) $(CFLAGS) -o shortest_path $(OBJ)  -lm -lilocplex -lconcert -lcplex -lpthread
 
shortest_path.o: shortest_path.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c shortest_path.cpp
 
clean:
	rm -f shortest_path shortest_path.o
