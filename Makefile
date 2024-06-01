output: main.o Vector2D.o Particle.o
	g++ main.o Vector2D.o Particle.o -o output -lraylib -lgdi32 -lwinmm

main.o: main.cpp Globals.h
	g++ -c main.cpp

Vector2D.o: Vector2D.cpp Vector2D.h Globals.h
	g++ -c Vector2D.cpp

Particle.o: Particle.cpp Particle.h Vector2D.h Globals.h
	g++ -c Particle.cpp

clean:
	rm *.o output