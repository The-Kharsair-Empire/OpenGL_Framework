output: main.o display.o shader.o
	g++ -o exe main.o display.o shader.o -lSDL2 -lGLEW -lGL -std=c++17

main.o: main.cpp
	g++ -c main.cpp 

display.o: display.cpp
	g++ -c display.cpp 

shader.o: shader.cpp
	g++ -c shader.cpp


clean:
	rm *.o