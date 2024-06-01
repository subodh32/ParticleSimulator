output: main.o Vector2D.o Particle.o Structure.o
	g++ main.o Vector2D.o Particle.o Structure.o -o output -lraylib -lgdi32 -lwinmm

main.o: main.cpp Globals.h
	g++ -c main.cpp

Vector2D.o: Vector2D.cpp Vector2D.h Globals.h
	g++ -c Vector2D.cpp

Particle.o: Particle.cpp Particle.h Vector2D.h Globals.h
	g++ -c Particle.cpp

Structure.o: Structure.cpp Structure.h Globals.h
	g++ -c Structure.cpp

clean:
	rm *.o output