all: g++
	@echo "Done."

g++: *.cpp
	g++ -g  *.cpp tinyxml/*.cpp interface/*.cpp tools/*.cpp -o cg -lGL -lGLU -lglut
	./cg arena_1.svg

clean:
	@rm -f *.o cg