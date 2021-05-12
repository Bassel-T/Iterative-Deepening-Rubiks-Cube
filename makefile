run:
	g++ -std=c++11 AStar.cpp Node.h
	./a.out $(START)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#